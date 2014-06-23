#define CLASS_NAME "BarrierDlg"
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include "debug.h"
#include "potential.h"
#include "model.h"
#include "barrierdlg.h"

/* 
 *  Constructs a SquareWellDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
BarrierDlg::BarrierDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : BarrierBase( parent, name, modal, fl )
{
	QIntValidator *intval = new QIntValidator(this);
	QDoubleValidator *doubleval = new QDoubleValidator(this);

	m_numPoints_edit->setValidator(intval);
	m_particleMass_edit->setValidator(doubleval);
	m_lowIntegration_edit->setValidator(doubleval);
	m_highIntegration_edit->setValidator(doubleval);
	m_eigenNumber_edit->setValidator(intval);
	m_extPotential_edit->setValidator(doubleval);
	m_potentialHighEdge_edit->setValidator(doubleval);
	m_potentialLowEdge_edit->setValidator(doubleval);
	m_barrierHighEdge_edit->setValidator(doubleval);
	m_barrierLowEdge_edit->setValidator(doubleval);
	m_barrierHeight_edit->setValidator(doubleval);
	m_richardson_checkbox->setChecked(true);
	
	m_recalcButton->setEnabled(false);

	setCaption("Barrier potential");
}

/*  
 *  Destroys the object and frees any allocated resources
 */
BarrierDlg::~BarrierDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

void BarrierDlg::slotDoCalc() {

	m_recalcButton->setEnabled(false);
	emit signalStartCalc();	
}

void BarrierDlg::slotTextChanged()
{
	if (m_lowIntegration_edit->text().isEmpty() ||
		m_highIntegration_edit->text().isEmpty() ||
		m_eigenNumber_edit->text().isEmpty() ||
		m_numPoints_edit->text().isEmpty() ||
		m_potentialLowEdge_edit->text().isEmpty() ||
		m_potentialHighEdge_edit->text().isEmpty() ||
		m_particleMass_edit->text().isEmpty() ||
		m_extPotential_edit->text().isEmpty() ||
		m_barrierLowEdge_edit->text().isEmpty() ||
		m_barrierHighEdge_edit->text().isEmpty() ||
		m_barrierHeight_edit->text().isEmpty()) return;

	m_recalcButton->setEnabled(true);
	
}


#include "barrierdlg.moc"
#include "barrierbase.moc"
