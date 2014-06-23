#include <qdom.h>
#include "system.h"
#include "squarewellpotential.h"


SquareWellPotential::SquareWellPotential(System *parent,
										double lowedge,
										double highedge,
										double highpot,
										double lowpot ) 	: Potential(parent)
{

	register unsigned int i;

	m_lowEdge = lowedge;
	m_highEdge = highedge;
	m_highPot = highpot;
	m_lowPot = lowpot;
	
	for (i = 0; i < m_system->points(); i++) {
		if (m_system->x(i) >= lowedge && m_system->x(i) <= highedge)
			m_y[i]=lowpot;
		else 
			m_y[i]=highpot;
	}
}

