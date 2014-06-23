#ifndef PARABOLICPOTENTIAL_H
#define PARABOLICPOTENTIAL_H

#include "potential.h"

class QDomElement;

class ParabolicPotential : public Potential {
public:
	ParabolicPotential(System *parent, double coeff );

	double coefficient() { return m_coefficient; }

protected:
	
	double m_coefficient;

};

#endif
