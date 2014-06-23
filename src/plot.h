#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include <qmap.h>
#include "control.h"

class QWidget;
class QMouseEvent;
class Palette;
class System;
class Project;

class Plot : public QwtPlot {
	Q_OBJECT
public:

	Plot(Project *project, QWidget *parent, const char *name);

	double 		getViewYSize() { return 1.0; }
	void 		traslate( Control::Command );
	void 		zoom( Control::Command );

public slots:
	void 		slotFetchData();
	void 		slotRefreshPalette();
	
protected:

	void		replotGraph();
	void		resetAxisScale();
	void		clearGraph();
	void 		replotCurve( unsigned int index );
	
	System 					*m_system;
	Project 				*m_project;
	QMap<unsigned int, long> m_tableMap;

};

#endif
