#include <qdom.h>
#include "system.h"
#include "potential.h"
#include "eigenvalue.h"

System::System(double low, double high, unsigned int npoints, double particleMass, unsigned int reqEigen ) {
	register unsigned int i;
	
	m_lowerValue = low;
	m_higherValue = high;
	m_points = npoints;
	m_curveList.setAutoDelete(true);
	m_particleMass = particleMass;
	m_requestedEigenNumber = reqEigen;
	m_hasExtrapolation = false;

	m_x = new double[m_points];
	double d = delta();
	for (i = 0; i < m_points; i++) m_x[i] = m_lowerValue + (d * i);
	
	
}

System::~System() {
	delete[] m_x;
}


