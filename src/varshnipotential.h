#ifndef VARSHNIPOTENTIAL_H
#define VARSHNIPOTENTIAL_H

#include "potential.h"

class QDomElement;

class VarshniPotential : public Potential {
public:
	VarshniPotential(System *parent,
								double de,
								double alpha, 
								double eqDistance, 
								unsigned int rot);

	double de() { return m_de; }
	double alpha() { return m_alpha; }
	double eqDistance() { return m_eqDistance; }
	unsigned int rotFactor() { return m_rotFactor; }

protected:
	
	double m_de;
	double m_alpha;
	double m_eqDistance;
	unsigned int m_rotFactor;

};

#endif
