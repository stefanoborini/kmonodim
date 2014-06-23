#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qvalidator.h>
#include "parabolicdlg.h"

ParabolicDlg::ParabolicDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : ParabolicBase( parent, name, modal, fl )
{

	QIntValidator *intval = new QIntValidator(this);
	QDoubleValidator *doubleval = new QDoubleValidator(this);

	m_highIntegration_edit->setValidator(doubleval);
	m_eigenNumber_edit->setValidator(intval);
	m_lowIntegration_edit->setValidator(doubleval);
	m_particleMass_edit->setValidator(doubleval);
	m_numPoints_edit->setValidator(intval);
	m_parabolicCoefficient_edit->setValidator(doubleval);
	m_richardson_checkbox->setChecked(true);	
	m_recalcButton->setEnabled(false);
	setCaption("Parabolic potential");
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ParabolicDlg::~ParabolicDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

void ParabolicDlg::slotDoCalc() {

	m_recalcButton->setEnabled(false);
	emit signalStartCalc();
}

void ParabolicDlg::slotTextChanged()
{
	// FIXME : catch checkbox events!
	if (m_lowIntegration_edit->text().isEmpty() ||
		m_highIntegration_edit->text().isEmpty() ||
		m_eigenNumber_edit->text().isEmpty() ||
		m_numPoints_edit->text().isEmpty() ||
		m_particleMass_edit->text().isEmpty() ||
		m_parabolicCoefficient_edit->text().isEmpty()) return;

	m_recalcButton->setEnabled(true);
	
}




#include "parabolicdlg.moc"
#include "parabolicbase.moc"
