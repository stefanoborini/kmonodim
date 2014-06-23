#include <malloc.h>
#include <qwt_math.h>
#include <qwt_plot.h>
#include <qpopupmenu.h>
#include <kcolordialog.h>
#include <qpen.h>
#include "palette.h"
#include "color.h"
#include "project.h"
#include "system.h"
#include "eigenvalue.h"
#include "potential.h"
#include "plot.h"
#include "control.h"
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif



Plot::Plot(Project *project, QWidget *parent, const char *name) : QwtPlot(parent, name) { 
	
	m_project = project;
	setMinimumSize(400,400);
	
}

void Plot::traslate( Control::Command c ) {
	static bool sw = false;
	int x = 0;
	int y = 0;

#ifdef HAVE_OLD_QWT
	double hy = axisScale(QwtPlot::yLeft).hBound();
	double ly = axisScale(QwtPlot::yLeft).lBound();
	
	double hx = axisScale(QwtPlot::xBottom).hBound();
	double lx = axisScale(QwtPlot::xBottom).lBound();
#else
	double hy = axisScale(QwtPlot::yLeft)->hBound();
	double ly = axisScale(QwtPlot::yLeft)->lBound();
	
	double hx = axisScale(QwtPlot::xBottom)->hBound();
	double lx = axisScale(QwtPlot::xBottom)->lBound();
#endif


	double xsize = hx-lx;
	double ysize = hy-ly;

	switch (c) {
		case Control::North: x=0; y=1; break;
		case Control::South: x=0; y=-1; break;
		case Control::East: x=1; y=0; break;
		case Control::West: x=-1; y=0; break;
		default:
			break;
	}

	setAxisScale(QwtPlot::yLeft, ly + ysize / 3 * y, hy + ysize / 3 * y);
	setAxisScale(QwtPlot::xBottom, lx + xsize / 3 * x, hx + xsize / 3 * x);
	
	replot();
	
}

void Plot::zoom( Control::Command c ) { 

#ifdef HAVE_OLD_QWT
	double hy = axisScale(QwtPlot::yLeft).hBound();
	double ly = axisScale(QwtPlot::yLeft).lBound();
	
	double hx = axisScale(QwtPlot::xBottom).hBound();
	double lx = axisScale(QwtPlot::xBottom).lBound();
#else
	double hy = axisScale(QwtPlot::yLeft)->hBound();
	double ly = axisScale(QwtPlot::yLeft)->lBound();
	
	double hx = axisScale(QwtPlot::xBottom)->hBound();
	double lx = axisScale(QwtPlot::xBottom)->lBound();
#endif

	double xsize = hx-lx;
	double ysize = hy-ly;

	if (c == Control::ZoomIn ) {
		setAxisScale(QwtPlot::yLeft, ly + ysize / 3 , hy - ysize / 3 );
//		setAxisScale(QwtPlot::xBottom, lx + xsize / 3 , hx - xsize / 3 );
	} else if (c == Control::ZoomOut) {
		setAxisScale(QwtPlot::yLeft, ly - ysize / 3 , hy + ysize / 3 );
//		setAxisScale(QwtPlot::xBottom, lx - xsize / 3 , hx + xsize / 3 );
	}

	replotGraph();
}





void Plot::slotFetchData() {
	resetAxisScale();
	replotGraph();
}

void Plot::slotRefreshPalette() {

	Palette *palette = m_project->palette();
	System *system = m_project->system();

	register unsigned int i;

	for (i = 0; i < system->curveNumber(); i++) {
		if (palette->changed(i)) {
			replotCurve( i );
		}
	}

	replot();
}

void Plot::clearGraph() {
	
	m_tableMap.clear();
	clear();
	
}
	
void Plot::replotGraph() {
	
	register unsigned int i;
	System *system = m_project->system();

	clearGraph();

	for ( i = 0;  i < system->curveNumber(); i++ ) {
		replotCurve( i );
	}
	
	replot();
}

void Plot::resetAxisScale() {
	System *system = m_project->system();
	Eigenvalue *e;
	float max = 0.;
	register unsigned int i;


	for ( i = 0;  i < system->eigenNumber(); i++ ) {
		e = system->eigenvalue(i);
		if (e->eigenvalue() > max) max = e->eigenvalue();
	}

	setAxisScale(QwtPlot::yLeft, -max*0.25 , max * 1.25 );
	setAxisScale(QwtPlot::xBottom, system->lowerValue(), system->higherValue());
}
	
void Plot::replotCurve(unsigned int index) { 
	
	Palette *palette = m_project->palette();
	System *system = m_project->system();
	Curve *curve;
	Color col;
	
	unsigned long key;

	if ( m_tableMap.contains(index) ) {
		removeCurve( m_tableMap[index] );
		m_tableMap.remove( index );
	}

	curve = system->curve( index );
	col = palette->color(index);
#ifdef HAVE_OLD_QWT
	double graphYSize = axisScale(QwtPlot::yLeft).hBound() - axisScale(QwtPlot::yLeft).lBound();
#else
	double graphYSize = axisScale(QwtPlot::yLeft)->hBound() - axisScale(QwtPlot::yLeft)->lBound();
#endif
	// FIXME curve->isEigenvalue
	if (curve->isEigenvalue()) curve->scaleToValue(graphYSize/4);
	
	if (col.active()) {
		double *temp = new double[system->points()];
		double *x = new double[system->points()];
		key = insertCurve(curve->name());
		m_tableMap.insert(index,key);

		setCurvePen( key,QPen( col ) );
		
//		double highLimit = axisScale(QwtPlot::yLeft)->hBound() + getViewYSize() * 2;
//		double lowLimit = axisScale(QwtPlot::yLeft)->lBound() - getViewYSize() * 2;

		double d;
		register unsigned int j;
		
// XXX : this was a fix for a bug in qt.
		for (j = 0; j < system->points(); j++) {
			x[j] = system->x(j);
//			d = curve->transformedY(j);
//			if (d > highLimit) temp[j] = highLimit;
//			else if (d < lowLimit ) temp[j] = lowLimit;
//			else temp[j] = d;
			temp[j] = curve->transformedY(j);
		}
		
		
		setCurveData( key, x, temp, system->points() );
		delete[] temp;
		delete[] x;
	}

}

#include "plot.moc"
