#include <qlineedit.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include "squarewelldlg.h"

/* 
 *  Constructs a SquareWellDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
SquareWellDlg::SquareWellDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : SquareWellBase( parent, name, modal, fl )
{

	QIntValidator *intval = new QIntValidator(this);
	QDoubleValidator *doubleval = new QDoubleValidator(this);

	m_highIntegration_edit->setValidator(doubleval);
	m_eigenNumber_edit->setValidator(intval);
	m_lowIntegration_edit->setValidator(doubleval);
	m_particleMass_edit->setValidator(doubleval);
	m_numPoints_edit->setValidator(intval);
	m_potentialLowEdge_edit->setValidator(doubleval);
	m_potentialHighEdge_edit->setValidator(doubleval);
	m_extPotential_edit->setValidator(doubleval);
	m_richardson_checkbox->setChecked(true);	
	
	m_recalcButton->setEnabled(false);
	setCaption("Square well potential");
}

/*  
 *  Destroys the object and frees any allocated resources
 */
SquareWellDlg::~SquareWellDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

void SquareWellDlg::slotDoCalc() {

	m_recalcButton->setEnabled(false);
	emit signalStartCalc();
}

void SquareWellDlg::slotTextChanged()
{
	if (m_lowIntegration_edit->text().isEmpty() ||
		m_highIntegration_edit->text().isEmpty() ||
		m_eigenNumber_edit->text().isEmpty() ||
		m_numPoints_edit->text().isEmpty() ||
		m_potentialLowEdge_edit->text().isEmpty() ||
		m_potentialHighEdge_edit->text().isEmpty() ||
		m_particleMass_edit->text().isEmpty() ||
		m_extPotential_edit->text().isEmpty()) return;

	m_recalcButton->setEnabled(true);
	
}




#include "squarewelldlg.moc"
#include "squarewellbase.moc"
