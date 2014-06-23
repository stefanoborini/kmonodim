#include <qlineedit.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include "morsedlg.h"

MorseDlg::MorseDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : MorseBase( parent, name, modal, fl )
{

	QIntValidator *intval = new QIntValidator(this);
	QDoubleValidator *doubleval = new QDoubleValidator(this);

	m_lowIntegration_edit->setValidator(doubleval);
	m_highIntegration_edit->setValidator(doubleval);
	m_eigenNumber_edit->setValidator(intval);
	m_particleMass_edit->setValidator(doubleval);
	m_numPoints_edit->setValidator(intval);
    m_rotFactor_edit->setValidator(intval);
    m_eqDistance_edit->setValidator(doubleval);
    m_alpha_edit->setValidator(doubleval);
    m_de_edit->setValidator(doubleval);
	m_richardson_checkbox->setChecked(true);

	m_recalcButton->setEnabled(false);
	setCaption("Morse potential");
}

/*  
 *  Destroys the object and frees any allocated resources
 */
MorseDlg::~MorseDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

void MorseDlg::slotDoCalc() {

	m_recalcButton->setEnabled(false);
	emit signalStartCalc();
}

void MorseDlg::slotTextChanged()
{
	if (m_lowIntegration_edit->text().isEmpty() ||
		m_highIntegration_edit->text().isEmpty() ||
		m_eigenNumber_edit->text().isEmpty() ||
		m_numPoints_edit->text().isEmpty() ||
		m_particleMass_edit->text().isEmpty() ||
		m_de_edit->text().isEmpty() ||
		m_rotFactor_edit->text().isEmpty() ||
		m_alpha_edit->text().isEmpty() ||
		m_eqDistance_edit->text().isEmpty()) return;
	
	m_recalcButton->setEnabled(true);
	
}




#include "morsedlg.moc"
#include "morsebase.moc"
