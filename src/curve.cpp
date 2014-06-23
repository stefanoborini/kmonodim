#include <math.h>
#include <qdom.h>
#include "system.h"
#include "curve.h"

Curve::Curve(System *parent) {
	m_system = parent;
	m_traslFactor = 0.;
	m_scaleFactor = 1.;
	m_y = new double[m_system->points()];
}

Curve::~Curve() {
	delete[] m_y;
}



double Curve::lowerValue() {
	double min = m_y[0];
	register unsigned int i;

	for (i = 0; i < m_system->points(); i++) {
		if (m_y[i] < min) min = m_y[i];
	}

	return min;
}

double Curve::higherValue() {
	double max = m_y[0];
	register unsigned int i;
	
	for (i = 0; i < m_system->points(); i++) {
		if (m_y[i] > max) max = m_y[i];
	}

	return max;
}

void Curve::scaleToValue(double value) {
	register unsigned int i;
	double max=0;
	
	// every (points / 10) points should be faster ?
	for (i = 0; i < m_system->points(); i++) 
		if (fabs(m_y[i]) > max) max = fabs(m_y[i]);
	
	m_scaleFactor = value/max;

}

unsigned int Curve::points() { return m_system->points(); }

