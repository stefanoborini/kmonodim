#ifndef POTENTIAL_H
#define POTENTIAL_H

#include <qstring.h>
#include "curve.h"


class System;

class Potential : public Curve {
public:
	Potential(System *parent) : Curve(parent) {}
	
	virtual double scaleFactor() { return 1.0; }
	virtual double traslateFactor() { return 0.0; }

	virtual QString name() { return QString("potential"); }

	virtual bool isPotential() { return true; }
	
};

#endif

