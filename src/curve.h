#ifndef CURVE_H 
#define CURVE_H

class System;
class QDomElement;
class QString;

class Curve {
public:
	
	Curve(System *parent); 
	~Curve();
	
	double higherValue();
	double lowerValue();

	inline double &y(unsigned int i) { return m_y[i]; }
	inline double &operator[](unsigned int i) { return m_y[i]; }
	inline const double transformedY(unsigned int i) const { return m_y[i] * scaleFactor() + traslateFactor(); }

	inline virtual double scaleFactor() const { return m_scaleFactor; }
	inline void setScaleFactor(double s) { m_scaleFactor = s; }
	virtual QString name() = 0;

	inline virtual double traslateFactor() const { return m_traslFactor; }
	inline void setTraslateFactor(double t) { m_traslFactor = t; }
	
	void scaleToValue(double value);

	unsigned int points();

	virtual bool isPotential() { return false; }
	virtual bool isEigenvalue() { return false; }
	
protected:

	double *m_y;
	System *m_system;
	double m_scaleFactor;
	double m_traslFactor;
};


#endif

