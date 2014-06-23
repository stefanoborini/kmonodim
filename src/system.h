#ifndef SYSTEM_H
#define SYSTEM_H

#include <qintdict.h>

class Potential;
class Eigenvalue;
class Curve;
class QDomElement;

class System {
public:
	System(double low, double high, unsigned int npoints, double particleMass, unsigned int reqEigen );
	~System();

	inline void 			setPotential(Curve *p) { m_curveList.replace(0,p); }
	inline void 			setEigenvalue(Curve *e, unsigned long index) { m_curveList.replace(index + 1,e); }
	inline void 			setHasExtrapolation(bool b) { m_hasExtrapolation = b; }
	
	inline double 			particleMass() { return m_particleMass; }
	inline double 			delta() { return (m_higherValue - m_lowerValue) / (m_points - 1); }
	inline unsigned int 	requestedEigenNumber() { return m_requestedEigenNumber; }
	inline double 			lowerValue() { return m_lowerValue; }
	inline double 			higherValue() { return m_higherValue; }
	inline unsigned int 	points() { return m_points; }
	inline bool 			hasExtrapolation() { return m_hasExtrapolation; }

	inline Potential *		potential() { return (Potential *)m_curveList[0]; }
	inline Eigenvalue *		eigenvalue(unsigned long i) { return (Eigenvalue *)m_curveList[i + 1]; }
	inline Curve *			curve(unsigned long i) { return m_curveList[i]; }
	inline unsigned int 	eigenNumber() { return m_curveList.count() - 1; }
	inline unsigned int 	curveNumber() { return m_curveList.count(); }
	inline double 			x(unsigned int i) { return m_x[i]; }

protected:
	
	double *m_x;
	QIntDict<Curve> m_curveList;
	double m_particleMass;
	double m_lowerValue;
	double m_higherValue;
	unsigned int m_points;
    unsigned int m_requestedEigenNumber;
	bool m_hasExtrapolation;
	
			
};

#endif
