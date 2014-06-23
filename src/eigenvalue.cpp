#include <math.h>
#include <qdom.h>
#include "system.h"
#include "eigenvalue.h"

Eigenvalue::Eigenvalue(System *parent) : Curve(parent) {

	m_eigenvalue = 0.;
	m_meanPotential = 0.;
	m_meanPosition = 0.;
	m_meanKinetic = 0.;
	m_hasWrongIntegrationLimits = false;

}
	

void Eigenvalue::normalize() {
	register unsigned int i;
	double n = 0.;

	for (i = 0; i < m_system->points(); i++) n += m_y[i]*m_y[i];
	n*=m_system->delta();
	
//	qDebug( "normalization factor n^2 = %g",n );
	
	n=1./sqrt(n);	
	for (i = 0; i < m_system->points(); i++) m_y[i] *= n;

}
