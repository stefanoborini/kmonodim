#include <qdom.h>
#include "system.h"
#include "parabolicpotential.h"


ParabolicPotential::ParabolicPotential(System *parent,
										double coeff) : Potential(parent)
{

	register unsigned int i;

	m_coefficient = coeff;
	

	for (i = 0; i < m_system->points(); i++) m_y[i]=0.5*m_coefficient*m_system->x(i)*m_system->x(i);
	
}

