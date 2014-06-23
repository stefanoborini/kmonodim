#include <qdom.h>
#include <math.h>
#include "system.h"
#include "morsepotential.h"

MorsePotential::MorsePotential(System *parent, 
								double de,
								double alpha, 
								double eqDistance, 
								unsigned int rot ) : Potential(parent)
{

	register unsigned int i;

	m_de = de;
	m_alpha = alpha;
	m_eqDistance = eqDistance;
	m_rotFactor = rot;

	double t,xt;
	
	for (i=0; i<m_system->points(); i++) {
		m_system->x(i) < 0 ? xt = m_system->delta() : xt=m_system->x(i);
		t = (1 - exp(-alpha*(xt-eqDistance)));
		m_y[i] = de * t * t + ( (double)(rot*rot+rot) / (2 * m_system->particleMass() * xt * xt));
	}
}
