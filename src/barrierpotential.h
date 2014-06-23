#ifndef BARRIERPOTENTIAL_H
#define BARRIERPOTENTIAL_H

#include "potential.h"

class BarrierPotential : public Potential {
public:
	BarrierPotential(System *parent,
						double lowedge,
						double highedge, 
						double highpot, 
						double lowpot, 
						double barrierlowedge, 
						double barrierhighedge, 
						double barrierheight );

	double lowEdge() { return m_lowEdge; }
	double highEdge() { return m_highEdge; }
	double highPot() { return m_highPot; }
	double lowPot() { return m_lowPot; }
	double barrierLowEdge() { return m_barrierLowEdge; }
	double barrierHighEdge() { return m_barrierHighEdge; }
	double barrierHeight() { return m_barrierHeight; }

protected:
	
	double m_lowEdge;
	double m_highEdge;
	double m_highPot;
	double m_lowPot;
	double m_barrierLowEdge;
	double m_barrierHighEdge;
	double m_barrierHeight;

};






#endif
