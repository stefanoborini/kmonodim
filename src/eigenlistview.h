#ifndef EIGENLISTVIEW_H
#define EIGENLISTVIEW_H
#include <qintdict.h>
#include "eigenlistviewbase.h"

class Model;
class MainWindow;
class QWidget;
class Project;
class Palette;
class EigenData;

class EigenListView : public EigenListViewBase
{ 
    Q_OBJECT;

public:
    EigenListView( Project *project, QWidget *parent = 0, const char* name = 0, WFlags fl = 0 );
	
	void enableRichardsonLabel(bool enable);
	void enableWrongLimitsLabel(bool enable);

public slots:

	void slotFetchData();
	void slotRefreshPalette();
	
protected slots:
	
//	void slotReportData();
//	void slotCheckVisibility();
	void slotItemClicked(QListViewItem *, const QPoint &, int);
	void slotSelectionChanged(QListViewItem *);
	void slotActivateAll();
	void slotSetUniqueColor();

protected:
	bool m_allActive;
	QIntDict<EigenData> m_dataDict;
	
	Project *m_project;

};

#endif // EIGENLISTVIEW_H
