#ifndef EIGENVALUE_H
#define EIGENVALUE_H

#include "curve.h"

class System;

class Eigenvalue : public Curve {
public:
	Eigenvalue(System *parent);

	void normalize();

	inline void setEigenvalue(double e) { m_eigenvalue = e; }
	inline void setExtrapolatedEigenvalue(double e) { m_extrapolatedEigenvalue = e; }
	inline void setMeanPotential(double m) { m_meanPotential = m; }
	inline void setMeanPosition(double m) { m_meanPosition = m; }
	inline void setMeanKinetic(double m) { m_meanKinetic = m; }
	inline void setHasWrongIntegrationLimits(bool a) { m_hasWrongIntegrationLimits = a; }

	inline double eigenvalue() const { return m_eigenvalue; }
	inline double extrapolatedEigenvalue() const { return m_extrapolatedEigenvalue; }
	inline bool hasWrongIntegrationLimits() const { return m_hasWrongIntegrationLimits; }
	inline double meanPotential() const { return m_meanPotential; }
	inline double meanPosition() const { return m_meanPosition; }
	inline double meanKinetic() const { return m_meanKinetic; }

	virtual double traslateFactor() const { return m_eigenvalue; }

	virtual QString name() { return QString("eigenvalue"); }

	virtual bool isEigenvalue() { return true; }

protected:
	double m_eigenvalue;
	double m_extrapolatedEigenvalue;
	double m_meanPotential;
	double m_meanPosition;
	double m_meanKinetic;
	bool m_hasWrongIntegrationLimits;

};

#endif
