#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <kmainwindow.h>
#include <kstatusbar.h>
#include <qlist.h>
#include <qtimer.h>
#include <qprogressbar.h>
#include "control.h"

class QPopupMenu;
class QTabWidget;
class Project;
class EigenListView;
class QWidgetStack;
class FileManager;
class ArrowPad;

class MainWindow : public KMainWindow {
	Q_OBJECT
public:
	MainWindow( const char *name );
	
	void 				statusMessage(const QString &str, int time=-1);
	QTabWidget *		tabWidget () { return m_tabWidget; }
	QWidgetStack *		widgetStack() { return m_widgetStack; }

protected slots:
	void 				slotCreateProjectSquareWell(); 
	void 				slotCreateProjectBarrier(); 
	void 				slotCreateProjectParabolic(); 
	void 				slotCreateProjectMorse(); 
	void 				slotCreateProjectVarshni(); 
	void 				slotCreateProjectFromFile();
	void 				slotCloseCurrentProject(void);
	void 				slotDataAvailable(Project *);
	void 				slotTabChanged();
	void 				slotSaveCurrentProject();
	void 				slotSaveCurrentProjectAs();
	void				slotFileMenuAboutToShow();
	void				slotViewMenuAboutToShow();
	void				slotArrowPadEvent(Control::Command);
	void				slotQuitApp();
	void				slotUpdateProgress(int);
	void				slotShowHideInputDialog();
	void				slotShowHideIntegralDialog();
		
protected:
	
	void 				addProject(Project *p, bool showDialog = true);
	Project *			activeProject(void);
	void 				saveProject(Project *p);
	void				createMenuBar();

	ArrowPad *			m_pad;
	FileManager *		m_fileManager;
	QPopupMenu *		m_fileMenu;
	QPopupMenu *		m_viewMenu;
	QPopupMenu *		file_newmenu;
	QTabWidget *		m_tabWidget;
	QWidgetStack *		m_widgetStack;
	QList<Project> 		m_projectList;
	QProgressBar *		m_progress;

	unsigned int 		m_projectCounter;

	
};

#endif
