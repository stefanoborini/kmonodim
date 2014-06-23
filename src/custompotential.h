#ifndef CUSTOMPOTENTIAL_H
#define CUSTOMPOTENTIAL_H

#include "potential.h"

class CustomPotential : public Potential {
public:
	CustomPotential(System *parent, double *array, unsigned int size);
	CustomPotential(System *parent, Potential *p);

	void build(double *array, unsigned int size);

};

#endif
