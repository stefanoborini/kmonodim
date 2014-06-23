#include <kapp.h>
#include <kmenubar.h>
#include <qpopupmenu.h>
#include <qtabwidget.h>
#include <qinputdialog.h>
#include <qhbox.h>
#include <qvbox.h>
#include <qgroupbox.h>
#include <qwidgetstack.h>
#include <kfiledialog.h>
#include "mainwindow.h"
#include "project.h"
#include "projectsquarewell.h"
#include "projectbarrier.h"
#include "projectparabolic.h"
#include "projectmorse.h"
#include "projectvarshni.h"
#include "arrowpad.h"
#include "eigenlistview.h"
#include "error.h"
#include "filemanager.h"

#include "plot.h"

extern Error *g_error;


MainWindow::MainWindow(const char *name) : KMainWindow( 0L ,name ) {

	m_projectCounter = 0;
	m_fileManager = new FileManager(this);

	createMenuBar();

	QHBox *hlay = new QHBox(this);
	hlay->setSpacing(5);	

	m_tabWidget = new QTabWidget(hlay,"TabWidget");
	QObject::connect(m_tabWidget,SIGNAL(currentChanged(QWidget *)), this, SLOT(slotTabChanged()));

	// FIXME : maybe a better interface?
	QGroupBox *gb = new QGroupBox("Command",hlay);
	gb->setColumnLayout(1, Qt::Vertical );
	
	QVBox *vlay = new QVBox(gb);
	ArrowPad *m_pad = new ArrowPad(vlay,"main");
	QObject::connect(m_pad, SIGNAL(signalAction(Control::Command)), this, SLOT(slotArrowPadEvent(Control::Command)));

	m_widgetStack = new QWidgetStack(vlay);

	setCentralWidget(hlay);
	m_projectList.setAutoDelete(true);
	m_progress = new QProgressBar(100, (QWidget *)statusBar(), "progress");
	statusBar()->addWidget(m_progress,0,true);
	m_progress->hide();
	
	statusMessage("Welcome to kmonodim!",2000);
	
	QObject::connect(m_fileManager, SIGNAL(signalProgress(int)), this, SLOT(slotUpdateProgress(int)) );

}

void MainWindow::statusMessage(const QString &str, int time) {
	
	if ( time < 0 ) statusBar()->message(str);
	else statusBar()->message(str, time); 

}


#define _MENUBAR_FILE_OPEN_ 1
#define _MENUBAR_FILE_QUIT_ 2
#define _MENUBAR_FILE_NEW_  3
#define _MENUBAR_FILE_CLOSE_ 4
#define _MENUBAR_FILE_SAVE_ 6
#define _MENUBAR_FILE_SAVE_AS_ 7

#define _MENUBAR_FILE_NEW_INF_ 20
#define _MENUBAR_FILE_NEW_SW_ 21
#define _MENUBAR_FILE_NEW_BARRIER_ 22
#define _MENUBAR_FILE_NEW_PARABOLIC_ 23
#define _MENUBAR_FILE_NEW_MORSE_ 24
#define _MENUBAR_FILE_NEW_VARSHNI_ 25
#define _MENUBAR_FILE_NEW_FROM_FILE_ 29

#define _MENUBAR_VIEW_INPUT_DIALOG_ 30
#define _MENUBAR_VIEW_INTEGRAL_DIALOG_ 31

void MainWindow::createMenuBar() {
	KMenuBar *menubar= menuBar();

	m_fileMenu=new QPopupMenu(this);
	file_newmenu= new QPopupMenu(this);
	file_newmenu->insertItem("Square well", this, SLOT(slotCreateProjectSquareWell()), 0,_MENUBAR_FILE_NEW_SW_);
	file_newmenu->insertItem("Barrier", this, SLOT(slotCreateProjectBarrier()), 0,_MENUBAR_FILE_NEW_BARRIER_);
	file_newmenu->insertItem("Parabolic", this, SLOT(slotCreateProjectParabolic()), 0,_MENUBAR_FILE_NEW_PARABOLIC_);
	file_newmenu->insertItem("Morse", this, SLOT(slotCreateProjectMorse()), 0,_MENUBAR_FILE_NEW_MORSE_);
	file_newmenu->insertItem("Varshni", this, SLOT(slotCreateProjectVarshni()), 0,_MENUBAR_FILE_NEW_VARSHNI_);
	file_newmenu->insertSeparator();
	file_newmenu->insertItem("From file...", this, SLOT(slotCreateProjectFromFile()), 0,_MENUBAR_FILE_NEW_FROM_FILE_);
	m_fileMenu->insertItem("New",file_newmenu,0,_MENUBAR_FILE_NEW_);

	m_fileMenu->insertItem("&Save",this,SLOT(slotSaveCurrentProject()), 0,_MENUBAR_FILE_SAVE_);
	m_fileMenu->insertItem("S&ave as...",this,SLOT(slotSaveCurrentProjectAs()), 0,_MENUBAR_FILE_SAVE_AS_);

	m_fileMenu->insertSeparator();
	m_fileMenu->insertItem("&Close current project",this,SLOT(slotCloseCurrentProject()), 0,_MENUBAR_FILE_CLOSE_);
	
	m_fileMenu->insertSeparator();
	m_fileMenu->insertItem("&Quit",this,SLOT(slotQuitApp()));
	menubar->insertItem("&File",m_fileMenu);

	m_viewMenu = new QPopupMenu(this);
	m_viewMenu->setCheckable(true);

	m_viewMenu->insertItem("Input dialog...",this,SLOT(slotShowHideInputDialog()),0,_MENUBAR_VIEW_INPUT_DIALOG_);
	m_viewMenu->insertItem("Integral evaluation...",this,SLOT(slotShowHideIntegralDialog()),0,_MENUBAR_VIEW_INTEGRAL_DIALOG_);
	menubar->insertItem("&View",m_viewMenu);

	QObject::connect(m_fileMenu, SIGNAL(aboutToShow()), this, SLOT(slotFileMenuAboutToShow()));
	QObject::connect(m_viewMenu, SIGNAL(aboutToShow()), this, SLOT(slotViewMenuAboutToShow()));

	
}


Project *MainWindow::activeProject(void) {

	Project *h;

	QListIterator<Project> it(m_projectList);

	for (; h = it.current(); ++it) if (h->plot() == m_tabWidget->currentPage() ) return h;

	return NULL;
	
}



void MainWindow::slotQuitApp() {
	kapp->quit();
}

void MainWindow::slotCreateProjectSquareWell() {
	bool ok = false;
    QString name;

	name.sprintf("SquareWell (%d)", ++m_projectCounter);
	Project *p = new ProjectSquareWell(this, name);
	addProject(p);
}

void MainWindow::slotCreateProjectBarrier() {
	bool ok = false;
    QString name;

	name.sprintf("Barrier (%d)", ++m_projectCounter);
	Project *p = new ProjectBarrier(this, name);
	addProject(p);
}

void MainWindow::slotCreateProjectParabolic() {
	bool ok = false;
    QString name;

	name.sprintf("Parabolic (%d)", ++m_projectCounter);
	Project *p = new ProjectParabolic(this, name);
	addProject(p);

}

void MainWindow::slotCreateProjectMorse() {
	bool ok = false;
    QString name;

	name.sprintf("Morse (%d)", ++m_projectCounter);
	Project *p = new ProjectMorse(this, name);
	addProject(p);

}

void MainWindow::slotCreateProjectVarshni() {
	bool ok = false;
    QString name;

	name.sprintf("Varshni (%d)", ++m_projectCounter);
	Project *p = new ProjectVarshni(this, name);
	addProject(p);

}

void MainWindow::slotCloseCurrentProject(void) {
	Project *p = activeProject();

	if (!p) {
		qDebug("p NULL in MainWindow::slotCloseCurrentProject()");
		return;
	}

	m_projectList.removeRef(p);
	
}
			
void MainWindow::slotSaveCurrentProjectAs(void) {

	Project *p = activeProject();
	
	if (!p) {
		qDebug("p NULL in MainWindow::slotSaveCurrentProjectAs()");
		return;
	}

	QString filename = KFileDialog::getSaveFileName(QString::null, "*.kmd", this,"Save as...");
	if (filename == QString::null) return;

	p->setFilename(filename);

	saveProject(p);

}

void MainWindow::slotSaveCurrentProject(void) {

	Project *p = activeProject();
	
	if (!p) {
		qDebug("p NULL in MainWindow::slotSaveCurrentProject()");
		return;
	}

	saveProject(p);
	
}

void MainWindow::saveProject(Project *p) {
	QString message;
	QString extmsg;
	QString str;

	QString filename = p->filename();

	statusMessage("Saving... please wait");
	m_progress->show();

	if (!m_fileManager->save(p,filename)) {
		switch(m_fileManager->status()) {
			case FileManager::NoWritePerms:
				message = "No write permission";
				extmsg = "Check the permissions on the file\nor the directories from the file manager";
				break;
			default:
				// boom
				message = "Unknown error";
				extmsg = "I'd like to know why";
		}

		str = "Unable to load %1:\n%2\n\n%3.";
		g_error->error("Unable to load file", str.arg(filename).arg(message).arg(extmsg));
	}

	m_progress->hide();
	statusMessage("Saving done",2000);
	
}


void MainWindow::slotCreateProjectFromFile() {
	
	QString filename = KFileDialog::getOpenFileName(QString::null, "*.kmd", this,"Load...");
	if (filename == QString::null) return;

	Project *p = m_fileManager->load(filename);

	QString message;
	QString extmsg;
	QString str;
	
	if ( !p ) {
		switch(m_fileManager->status()) {
			case FileManager::FileNotFound:
				message = "File not found";
				extmsg = "The file was either deleted or moved";
				break;
			case FileManager::NoReadPerms:
				message = "No read permission";
				extmsg = "Check the permissions on the file\nor the directories from the file manager";
				break;
			case FileManager::ParseError:
				message = "Error while parsing xml data";
				extmsg = "The file is corrupted or mangled";
				break;
			case FileManager::InvalidProjectType:
				message = "Invalid project type";
				extmsg = "The project type is unknown or not supported";
				break;
			case FileManager::InvalidXMLData:
				message = "Invalid XML data";
				extmsg = "The file contains unconsistent data";
				break;
			default:
				// boom
				message = "Unknown error";
				extmsg = "I'd like to know why";
		}

		str = "Unable to load %1:\n%2\n\n%3.";
		g_error->error("Unable to load file", str.arg(filename).arg(message).arg(extmsg));
		return;
	}

	addProject(p, false);

}



void MainWindow::slotFileMenuAboutToShow() {
	
	Project *p = activeProject();
	bool flag;
	
	flag = ( p && ! p->isRunning());
	m_fileMenu->setItemEnabled(_MENUBAR_FILE_CLOSE_, flag);
	
	flag = ( p && ! p->isRunning() && p->hasValidData());
	m_fileMenu->setItemEnabled(_MENUBAR_FILE_SAVE_, flag);
	m_fileMenu->setItemEnabled(_MENUBAR_FILE_SAVE_AS_, flag);
}

void MainWindow::slotViewMenuAboutToShow() {
	
	Project *p = activeProject();
	bool flag;
	
	if (p) {
		m_viewMenu->setItemEnabled(_MENUBAR_VIEW_INPUT_DIALOG_, true);
		m_viewMenu->setItemEnabled(_MENUBAR_VIEW_INTEGRAL_DIALOG_, true);
		m_viewMenu->setItemChecked(_MENUBAR_VIEW_INPUT_DIALOG_, p->inputDialog()->isVisible());
		m_viewMenu->setItemChecked(_MENUBAR_VIEW_INTEGRAL_DIALOG_, p->integralDialog()->isVisible());
	} else {
		m_viewMenu->setItemEnabled(_MENUBAR_VIEW_INPUT_DIALOG_, false);
		m_viewMenu->setItemEnabled(_MENUBAR_VIEW_INTEGRAL_DIALOG_, false);
		m_viewMenu->setItemChecked(_MENUBAR_VIEW_INPUT_DIALOG_, false);
		m_viewMenu->setItemChecked(_MENUBAR_VIEW_INTEGRAL_DIALOG_, false);
	}
	
}

void MainWindow::slotDataAvailable(Project *project) {

	Project *p = activeProject();

	if (project == p) slotTabChanged();

}

void MainWindow::slotTabChanged() {
	
	Project *p = activeProject();

	if (!p) return;

	m_widgetStack->raiseWidget(p->eigenListView());

}

void MainWindow::slotArrowPadEvent(Control::Command c) {

	Project *p = activeProject();

	if (!p) return;

	switch (c) {
		case Control::North:
		case Control::South:
		case Control::East:
		case Control::West:
			p->plot()->traslate(c);
			break;
		case Control::ZoomIn:
		case Control::ZoomOut:
			p->plot()->zoom(c);
			break;
		default:
			break;
	}
	
}

void MainWindow::slotUpdateProgress(int progress) {
	m_progress->setProgress(progress);
	kapp->processEvents();
}

void MainWindow::slotShowHideInputDialog() {
	Project *p = activeProject();
	
	if (m_viewMenu->isItemChecked(_MENUBAR_VIEW_INPUT_DIALOG_)) {
		m_viewMenu->setItemChecked(_MENUBAR_VIEW_INPUT_DIALOG_,false);
		p->inputDialog()->hide();
	} else {
		m_viewMenu->setItemChecked(_MENUBAR_VIEW_INPUT_DIALOG_,true);
		p->inputDialog()->show();
	}

}	

void MainWindow::slotShowHideIntegralDialog() {
	Project *p = activeProject();
	
	if (m_viewMenu->isItemChecked(_MENUBAR_VIEW_INTEGRAL_DIALOG_)) {
		m_viewMenu->setItemChecked(_MENUBAR_VIEW_INTEGRAL_DIALOG_,false);
		p->integralDialog()->hide();
	} else {
		m_viewMenu->setItemChecked(_MENUBAR_VIEW_INPUT_DIALOG_,true);
		p->integralDialog()->show();
	}

}	


void MainWindow::addProject(Project *p, bool showDialog) {

	QObject::connect(p,SIGNAL(signalDataAvailable(Project *)), this, SLOT(slotDataAvailable(Project *)));
	m_projectList.append(p);
	if (showDialog) p->inputDialog()->show();
}


#include "mainwindow.moc"


