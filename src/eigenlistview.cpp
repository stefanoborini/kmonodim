#include <qpushbutton.h>
#include <kcolordialog.h>
#include <qlabel.h>

#include "eigenlistview.h"
#include "mylistviewitem.h"
#include "eigenvalue.h"
#include "project.h"
#include "palette.h"
#include "color.h"
#include "system.h"
#include "potential.h"
#include "eigenvalue.h"


class EigenData {
public:
	double eigenvalue;
	double extrapolatedEigenvalue;
	double meanPosition;
	double meanKinetic;
	double meanPotential;
	bool wrongLimits;
	bool isEigenvalue;
};


/* 
 *  Constructs a EigenListView which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
EigenListView::EigenListView( Project *project, QWidget *parent, const char* name, WFlags fl )
    : EigenListViewBase( parent, name, fl )
{
	m_project = project; 

	m_listView->setSelectionMode(QListView::Single);
	m_listView->setRootIsDecorated(true);
	m_listView->setTreeStepSize(10);

	m_allActive=true;
	m_setActiveButton->setText("Disable all");
	
	m_eigenvalue_label->setText("-");
	m_extrapolatedEigenvalue_label->setText("-");
	enableRichardsonLabel(false);
	enableWrongLimitsLabel(false);
	m_meanPotential_label->setText("-");
	m_meanKinetic_label->setText("-");
	m_meanPosition_label->setText("-");

	m_dataDict.setAutoDelete(true);

	QObject::connect(m_listView,SIGNAL(clicked(QListViewItem *, const QPoint &, int)), this,SLOT(slotItemClicked(QListViewItem *, const QPoint &, int)));
	QObject::connect(m_listView,SIGNAL(selectionChanged(QListViewItem *)), this,SLOT(slotSelectionChanged(QListViewItem *)));
	QObject::connect(m_setActiveButton,SIGNAL(clicked()), this,SLOT(slotActivateAll()));
	QObject::connect(m_setUniqueColorButton,SIGNAL(clicked()), this,SLOT(slotSetUniqueColor()));
}


void EigenListView::slotFetchData() {
	register unsigned int i;
	double min;
	System *system;
	Palette *palette;
	Eigenvalue *e;
	QListViewItem *select = NULL;
	QString str;
	int digits;
	
	m_listView->clear();
	m_dataDict.clear();
	
	system = m_project->system();
	palette = m_project->palette();
	
	enableRichardsonLabel(system->hasExtrapolation());
	
	Color col = palette->color(0);
	
	str.sprintf("Potential");

	MyListViewItem *rootitem = new MyListViewItem(m_listView, 0, str, col, col.active(), false);
	EigenData *data = new EigenData;
	data->isEigenvalue = false;
	m_dataDict.insert(0,data);
	
	for ( i = 0;  i < system->eigenNumber(); i++ ) { 
		e = system->eigenvalue( i );
		col = palette->color( i + 1 );
		str.sprintf("%d",(int)e->eigenvalue());
		digits = str.length();
		digits += 6;
		str.sprintf("%.*g",digits,e->eigenvalue());
		MyListViewItem *item = new MyListViewItem(rootitem, i + 1, str, col, col.active(),e->hasWrongIntegrationLimits());
		if (!i) select = item;
			
		data = new EigenData;
		data->eigenvalue = e->eigenvalue();
		data->extrapolatedEigenvalue = e->extrapolatedEigenvalue();
		data->meanPotential = e->meanPotential();
		data->meanKinetic = e->meanKinetic();
		data->meanPosition = e->meanPosition();
		data->wrongLimits = e->hasWrongIntegrationLimits();
		data->isEigenvalue = true;
		m_dataDict.insert(i+1, data);
		
	}
	
	m_listView->setOpen(rootitem,true);
	m_listView->setSorting(0,false);
	
	if (select) m_listView->setSelected(select,true);

}	
		

void EigenListView::slotItemClicked(QListViewItem *item, const QPoint &point, int c) {

	if (!item) return;

	int index;
	int result;
	MyListViewItem *it = (MyListViewItem *)item;
	Palette *palette = m_project->palette();
	Color col;
 
	KColorDialog coldlg(this,"colordialog",TRUE);
	index = it->getDataIndex();
	col = palette->color(index);

	switch (c) {
		case 1: // clicked on the color
			coldlg.setColor(col);
			if (coldlg.exec() == KColorDialog::Accepted) {
				col = coldlg.color();
				palette->setColor( index, col );
			}
			palette->reportChanges();
			break;
		case 2: // clicked on the active spot
			col.setActive(!col.active());
			palette->setColor( index, col );
			palette->reportChanges();
			break;
	}

}

void EigenListView::slotSelectionChanged(QListViewItem *item) {

	if (!item) return;
	
	QString str;
	MyListViewItem *it = (MyListViewItem *)item;
	int index = it->getDataIndex();
	int digits;

	EigenData *data;
	data = m_dataDict[index];
	if (data && data->isEigenvalue) {

		str.sprintf("%d",(int)data->eigenvalue);
		digits = str.length();
		digits += 6;
		str.sprintf("%.*g",digits,data->eigenvalue);
		m_eigenvalue_label->setText(str);

		str.sprintf("%d",(int)data->extrapolatedEigenvalue);
		digits = str.length();
		digits += 6;
		str.sprintf("%.*g",digits,data->extrapolatedEigenvalue);
		m_extrapolatedEigenvalue_label->setText(str);
		
		str.sprintf("%d",(int)data->meanPotential);
		digits = str.length();
		digits += 6;
		str.sprintf("%.*g",digits,data->meanPotential);
		m_meanPotential_label->setText(str);

		str.sprintf("%d",(int)data->meanKinetic);
		digits = str.length();
		digits += 6;
		str.sprintf("%.*g",digits,data->meanKinetic);
		m_meanKinetic_label->setText(str);

		str.sprintf("%d",(int)data->meanPosition);
		digits = str.length();
		digits += 6;
		str.sprintf("%.*g",digits,data->meanPosition);
		m_meanPosition_label->setText(str);

		enableWrongLimitsLabel(data->wrongLimits);
	} else {
		m_eigenvalue_label->setText("-");
		m_extrapolatedEigenvalue_label->setText("-");
		m_meanPotential_label->setText("-");
		m_meanKinetic_label->setText("-");
		m_meanPosition_label->setText("-");
	}

}

void EigenListView::slotRefreshPalette() {
	MyListViewItem *item;
	int index;
	QListViewItemIterator it(m_listView);
	
	Palette *palette = m_project->palette();

	for (; item = (MyListViewItem *)it.current(); ++it) {
		index = item->getDataIndex();
		if (palette->changed(index)) {
			Color col = palette->color( index );
			item->setActive(col.active());
			item->setColor(col);
		}
	}
}


void EigenListView::slotActivateAll() {
	QListViewItemIterator it(m_listView);
	MyListViewItem *item;
	Palette *palette = m_project->palette();
	Color col;
	unsigned int index;

	m_allActive=!m_allActive;
	
	for (; it.current() ; ++it) {
		item = (MyListViewItem *)it.current();
		index = item->getDataIndex();
		col = palette->color(index);
		col.setActive(m_allActive);
		palette->setColor( index, col );
	}
	
	palette->reportChanges();
	m_allActive ? m_setActiveButton->setText("Disable all") : m_setActiveButton->setText("Enable all");

}
	
void EigenListView::slotSetUniqueColor() {
	QListViewItemIterator it(m_listView);
	MyListViewItem *item;
	Color col;
	QColor newcol;
	unsigned int index;
	Palette *palette = m_project->palette();

	int result;

	if ( KColorDialog::getColor( newcol ) == KColorDialog::Accepted ) {
		for (; it.current() ; ++it) {
			item = (MyListViewItem *)it.current();
			index = item->getDataIndex();
			col = palette->color(index);
			col.setColor(newcol);
			palette->setColor(index,col);
		}
	}		
	palette->reportChanges();
}

void EigenListView::enableRichardsonLabel(bool enable) {

	qDebug("enableRichardsonLabel called");

	if (enable) {
		qDebug("enable label");
		m_extrapolatedEigenvalue_label->show();
		m_extrapolatedEigenvalue_name_label->show();
		resize(sizeHint());
	} else {
		qDebug("disable label");
		m_extrapolatedEigenvalue_label->hide();
		m_extrapolatedEigenvalue_name_label->hide();
		resize(sizeHint());
	}
}

void EigenListView::enableWrongLimitsLabel(bool enable) {
	if (enable) m_wrongLimits_label->show();
	else m_wrongLimits_label->hide();
}

#include "eigenlistview.moc"
#include "eigenlistviewbase.moc"

