#define CLASS_NAME "InfiniteDlg"
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include "debug.h"
#include "potential.h"
#include "model.h"
#include "infinite.h"

/* 
 *  Constructs a InfiniteDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
InfiniteDlg::InfiniteDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : InfiniteBase( parent, name, modal, fl )
{

	QIntValidator *intval = new QIntValidator(this);
	QDoubleValidator *doubleval = new QDoubleValidator(this);
	m_eigenNumber_edit->setValidator(intval);
	m_particleMass_edit->setValidator(doubleval);
	m_numPoints_edit->setValidator(intval);
	m_lowEdge_edit->setValidator(doubleval);
	m_highEdge_edit->setValidator(doubleval);
	
	setCaption("Infinite well potential");
	m_recalcButton->setEnabled(false);
}

/*  
 *  Destroys the object and frees any allocated resources
 */
InfiniteDlg::~InfiniteDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

void InfiniteDlg::slotDoCalc() {

	m_recalcButton->setEnabled(false);
	emit signalStartCalc();
		
}

void InfiniteDlg::slotTextChanged()
{
	if (m_eigenNumber_edit->text().isEmpty() ||
		m_numPoints_edit->text().isEmpty() ||
		m_lowEdge_edit->text().isEmpty() ||
		m_particleMass_edit->text().isEmpty() ||
		m_highEdge_edit->text().isEmpty()) return;

	m_recalcButton->setEnabled(true);
	
}


#include "infinite.moc"
#include "infinitebase.moc"
