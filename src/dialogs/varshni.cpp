#define CLASS_NAME "VarshniDlg"
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qvalidator.h>

#include "debug.h"
#include "potential.h"
#include "model.h"
#include "varshni.h"

/* 
 *  Constructs a VarshniDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
VarshniDlg::VarshniDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : VarshniBase( parent, name, modal, fl )
{

	QIntValidator *intval = new QIntValidator(this);
	QDoubleValidator *doubleval = new QDoubleValidator(this);
	
    m_highIntegration_edit->setValidator(doubleval);
    m_lowIntegration_edit->setValidator(doubleval);
    m_particleMass_edit->setValidator(doubleval);
    m_rotFactor_edit->setValidator(doubleval);
    m_eqDistance_edit->setValidator(doubleval);
    m_alpha_edit->setValidator(doubleval);
    m_de_edit->setValidator(doubleval);
    m_eigenNumber_edit->setValidator(intval);
    m_numPoints_edit->setValidator(intval);

	m_recalcButton->setEnabled(false);
	setCaption("Varshni potential");
}

/*  
 *  Destroys the object and frees any allocated resources
 */
VarshniDlg::~VarshniDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

void VarshniDlg::slotDoCalc() {

	m_recalcButton->setEnabled(false);
	emit signalStartCalc();
		
}

void VarshniDlg::slotTextChanged()
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


#include "varshni.moc"
#include "varshnibase.moc"
