#ifndef INTEGRAL_H 
#define INTEGRAL_H
#include "integralbase.h"

class Project;

class Integral : public IntegralBase
{ 
    Q_OBJECT;

public:
    Integral( Project *project, QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Integral();
	
protected slots:
    void 			slotFetchData();
	void 			slotRecalc();

protected:
	Project *		m_project;

	
};

#endif 
