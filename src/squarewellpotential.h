#ifndef SQUAREWELLPOTENTIAL_H
#define SQUAREWELLPOTENTIAL_H

#include "potential.h"

class QDomElement;

class SquareWellPotential : public Potential {
public:
	SquareWellPotential(System *parent, double lowedge, double highedge, double highpot, double lowpot );

	double lowEdge() { return m_lowEdge; }
	double highEdge() { return m_highEdge; }
	double highPot() { return m_highPot; }
	double lowPot() { return m_lowPot; }

protected:
	
	double m_lowEdge;
	double m_highEdge;
	double m_highPot;
	double m_lowPot;

};

#endif
