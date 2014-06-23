#include <qmessagebox.h>
#include <qtabwidget.h>
#include <qhbox.h>
#include <qlayout.h>
#include <qwidgetstack.h>
#include <qfile.h>
#include <iostream>
#include "plot.h"
#include "mainwindow.h"
#include "model.h"
#include "system.h"
#include "color.h"
#include "palette.h"
#include "project.h"
#include "eigenlistview.h"
#include "integral.h"
#include "error.h"
#include "xmlutils.h"

extern Error *g_error;

Project::Project(MainWindow *mw, QString name) : QObject(mw) {

	m_mainWindow = mw;
	m_name = name;
	m_filename = name;
	m_model = new Model(this);
	m_palette = new Palette(this);
	m_plot = new Plot(this,m_mainWindow->tabWidget(),"plot");
	QVBoxLayout *vbl = new QVBoxLayout(m_mainWindow->widgetStack());
	m_eigenList = new EigenListView(this, m_mainWindow->widgetStack(),"eigenList");
	vbl->addWidget(m_eigenList);
	m_integral = new Integral(this,m_mainWindow,"integraldialog");
	m_integral->hide();
	m_system = NULL;

	m_mainWindow->tabWidget()->addTab(m_plot,m_name);
	m_plot->setMinimumSize(0,0);
	m_mainWindow->tabWidget()->setMinimumSize(m_plot->sizeHint());
	m_mainWindow->tabWidget()->showPage(m_plot);
	m_plot->replot();

	m_mainWindow->widgetStack()->raiseWidget(m_eigenList);
	m_mainWindow->widgetStack()->setMinimumSize(m_eigenList->sizeHint());

	QObject::connect(m_model, SIGNAL(signalDone()), this, SLOT(slotCheckModel()));
	QObject::connect(this, SIGNAL(signalDataAvailable(Project *)), m_plot, SLOT(slotFetchData()));
	QObject::connect(this, SIGNAL(signalDataAvailable(Project *)), m_eigenList, SLOT(slotFetchData()));
	QObject::connect(this, SIGNAL(signalDataAvailable(Project *)), m_integral, SLOT(slotFetchData()));
	QObject::connect(m_palette, SIGNAL(signalChanged()), m_plot, SLOT(slotRefreshPalette()));
	QObject::connect(m_palette, SIGNAL(signalChanged()), m_eigenList, SLOT(slotRefreshPalette()));


}

Project::~Project() {
	m_plot->hide();
	m_mainWindow->tabWidget()->removePage(m_plot);
	m_mainWindow->widgetStack()->removeWidget(m_eigenList);
	
	delete m_plot;
	delete m_eigenList;

	if (m_system) delete m_system;
}

void Project::setName(const QString &name) {
	m_name = name;
	m_mainWindow->tabWidget()->changeTab(m_plot,name);
}

void Project::setFilename(const QString &filename) {
	m_filename = filename;
}


// and finally we are here....
void Project::slotCheckModel() {

	bool critical = false;

	System *sys = m_model->currentSystem();

	switch (m_model->status()) {
		case Model::E_Ok:
			break;
		case Model::E_WrongIntegrationLimits:
			g_error->error("Wrong integration limits","The integration space you specified\ndoesn't permit a regular wavefunction.\nFor this reason, the incorrect eigenfunctions were dropped.");
			break;
		case Model::E_DiagonalizationFailed:
			g_error->error("Diagonalization failed","Damn! The diagonalization step was unsuccessful.\n Light up some candle and pray Heisemberg, then try to understand what happens.\n");
			critical = true;
			break;
		case Model::E_RichardsonDiagonalizationFailed:
			g_error->error("Richardson diagonalization failed","Damn! The richardson diagonalization step was unsuccessful.\n Light up some candle and pray Heisemberg, then try to understand what happens.\n");
			critical = true;
			break;
		default:
			g_error->error("Nasty happen","Unhandled model status in Project::slotCheckModel.\n");
			critical = true;
	}

	// a critical error occur... so the system is crap and we can free it.
	if (critical) {
		delete sys;
		return;
	}
	
	// good... the system is valid... let's delete the current system, if there's
	// one, and place the model output on the project.
	if (m_system) {
		delete m_system;
		m_system = NULL;
	}
	m_system = sys;

	for (unsigned int i = 0; i < m_system->curveNumber(); i++) {
		if (m_palette->color(i) == Color::null) m_palette->setColor(i,Color(255,0,0,true));
	}
	m_palette->resetChanged();

	emit signalDataAvailable(this);
}

void Project::XMLSave(QDomElement &root) {

	if (!m_system) return;

	emit signalProgress(0);
	
	QDomDocument doc = root.ownerDocument();
	QDomElement project = doc.createElement("project");
	project.setAttribute("type",typeName());
	root.appendChild(project);

	QDomElement name = doc.createElement("name");
	QDomText text = doc.createTextNode(m_name);
	name.appendChild(text);
	project.appendChild(name);	
	
	emit signalProgress(10);

	XMLSaveSystem(project);

	emit signalProgress(80);

	XMLSavePalette(project);

	emit signalProgress(100);

}	


void Project::XMLSavePalette(QDomElement &project) {
	register unsigned int i,b;
	Color col;


	QDomDocument doc = project.ownerDocument();
	QDomElement palette = doc.createElement("palette");
	QDomElement color;

	project.appendChild(palette);
	
	for (i = 0; i < m_palette->size(); i++) {
		col = m_palette->color(i);
		color = doc.createElement("color");
		color.setAttribute("value", col.name());
		b = col.active() ? 1 : 0;
		color.setAttribute("active",b);
		palette.appendChild(color);
	}
	
}


bool Project::XMLLoad(const QDomElement &root) {
	bool flag = true;
	
	QDomElement project = XMLUtils::childWithTag(root,"project");

	if (project.isNull()) return false;
	
	// first we load the palette, since after the system is loaded
	// the model triggers immediately an update, so the palette must be
	// ready at the call of the slotCheckModel()
	if (!XMLLoadPalette(project)) return false;
	if (!XMLLoadSystem(project)) return false;

}

bool Project::XMLLoadPalette(const QDomElement &project) {
	register unsigned int i;
	bool flag = true;

	QDomElement palette = XMLUtils::childWithTag(project,"palette");

	if (palette.isNull()) return false;

	QDomNodeList nodelist = palette.childNodes();
	QDomElement elem;
	QString colorstring;
	bool active;
	
	for (i = 0; i < nodelist.count(); i++) {
		elem = nodelist.item(i).toElement();
		if (elem.isNull() || elem.tagName() != "color") continue;
		active = (elem.attribute("active","1").toUInt() != 0);
		colorstring = elem.attribute("value","#ff0000");
		m_palette->setColor(i,Color(colorstring,active));
	}

	return true;
	
}

QDialog *Project::integralDialog() { return m_integral; }


#include "project.moc"


