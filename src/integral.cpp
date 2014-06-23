#include <qcombo.h>
#include <qlabel.h>
#include "project.h"
#include "system.h"
#include "potential.h"
#include "eigenvalue.h"
#include "integralbase.h"
#include "integral.h"

Integral::Integral( Project *project, QWidget *parent, const char* name, WFlags fl )
    : IntegralBase( parent, name, fl )
{

	m_project = project;
	QString str;
	str.sprintf("Integral Evaluation");
	setCaption(str);
	setFixedSize(sizeHint());

	m_firstEigenCombo->setEditable(false);
	m_secondEigenCombo->setEditable(false);
	m_operatorCombo->setEditable(false);

	m_firstEigenCombo->setEnabled(false);
	m_secondEigenCombo->setEnabled(false);
	m_operatorCombo->setEnabled(false);
	
	m_operatorCombo->insertItem("1",0);
	m_operatorCombo->insertItem("x",1);
	m_operatorCombo->insertItem("x^2",2);
	m_operatorCombo->insertItem("x^3",3);
	m_operatorCombo->insertItem("V",4);
	m_operatorCombo->insertItem("T",5);
	
	m_valueLabel->setText("?");
	
}

/*  
 *  Destroys the object and frees any allocated resources
 */
Integral::~Integral()
{
    // no need to delete child widgets, Qt does it all for us
}


void Integral::slotFetchData() {
	register unsigned int i;
	System *system;
	Eigenvalue *e;
	QString str;
	int digits;

	m_firstEigenCombo->clear();
	m_secondEigenCombo->clear();

	m_firstEigenCombo->setEnabled(true);
	m_secondEigenCombo->setEnabled(true);
	m_operatorCombo->setEnabled(true);

	system = m_project->system();

	for (i = 0; i < system->eigenNumber(); i++) {
		e = system->eigenvalue(i);
		str.sprintf("%d",(int)e->eigenvalue());
		digits = str.length();
		digits += 6;
		str.sprintf("%d: %.*g",i+1,digits,e->eigenvalue());
		m_firstEigenCombo->insertItem(str,i);
		m_secondEigenCombo->insertItem(str,i);
	}	

	slotRecalc();

}


void Integral::slotRecalc() {
	double sum = 0.;
	System *system;
	Eigenvalue *e1,*e2;
	Potential *p;
	register unsigned int i;

	if (!m_project->hasValidData()) return;

	system = m_project->system();
	
	e1 = system->eigenvalue(m_firstEigenCombo->currentItem());
	e2 = system->eigenvalue(m_secondEigenCombo->currentItem());
	p = system->potential();
	
	switch( m_operatorCombo->currentItem() ) {
		case 0: 
        	for (i = 0; i < system->points(); i++) sum += e1->y(i)*e2->y(i);
        	sum*=system->delta();
			break;
		case 1:
        	for (i = 0; i < system->points(); i++) sum += e1->y(i)*e2->y(i) * system->x(i);
        	sum*=system->delta();
			break;
		case 2:
        	for (i = 0; i < system->points(); i++) sum += e1->y(i)*e2->y(i) * system->x(i) * system->x(i);
    	    sum*=system->delta();
			break;
		case 3:
        	for (i = 0; i < system->points(); i++) sum += e1->y(i) * e2->y(i) * system->x(i) * system->x(i) * system->x(i);
    	    sum*=system->delta();
			break;
		case 4:
			for (i = 0; i < system->points(); i++) sum += e1->y(i) * e2->y(i) * p->y(i);
			sum*=system->delta();
			break;
		case 5:
			for (i = 1; i < system->points()-1; i++) sum += e1->y(i) * ( e2->y(i+1) + e2->y(i-1) - 2 * e2->y(i) );
			sum *= 1 / ( - 2 * system->particleMass() * system->delta());
			break;

	}
	QString str;
	str.sprintf("%g",sum);
	m_valueLabel->setText(str);
	
}

#include "integral.moc"
#include "integralbase.moc"

