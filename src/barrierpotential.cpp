#include "system.h"
#include "barrierpotential.h"

BarrierPotential::BarrierPotential(System *parent, 
									double lowedge,
									double highedge,
									double highpot,
									double lowpot,
									double barrierlowedge,
									double barrierhighedge,
									double barrierheight ) : Potential(parent)
{

	register unsigned int i;

	m_lowEdge = lowedge;
	m_highEdge = highedge;
	m_highPot = highpot;
	m_lowPot = lowpot;
	m_barrierLowEdge = barrierlowedge;
	m_barrierHighEdge = barrierhighedge;
	m_barrierHeight = barrierheight;

	for (i = 0; i < m_system->points(); i++) {
		if (m_system->x(i) <= lowedge || m_system->x(i) >= highedge ) m_y[i] = highpot;
		else if (m_system->x(i) >= barrierlowedge && m_system->x(i) < barrierhighedge) m_y[i] = barrierheight;
		else m_y[i] = lowpot;
	}
}
