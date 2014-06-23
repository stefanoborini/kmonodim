#include "system.h"
#include "custompotential.h"

CustomPotential::CustomPotential(System *parent, double *array, unsigned int size) : Potential(parent)
{
	m_system = parent;

	build(array,size);

}

CustomPotential::CustomPotential(System *parent, Potential *p) : Potential(parent)
{

	register unsigned int i;
	m_system = parent;

	double *array = new double[p->points()];

	for (i = 0 ; i < p->points(); i++) {
		array[i] = p->y(i);
	}
	
	build(array, p->points());

	delete[] array;
}

void CustomPotential::build(double *array, unsigned int size) {
	
	register unsigned int i, offset;
	double prop = size / m_system->points();
	double interp;

	for (i = 0; i < m_system->points(); i++) {
		offset = (unsigned int) (i * prop);
		interp = (i * prop) - (double) offset;
		m_y[i] = array[offset] + ( array[offset+1] - array[offset] ) * interp;
		qDebug("m_y[%d] = %g",i, m_y[i]);

	}

}
