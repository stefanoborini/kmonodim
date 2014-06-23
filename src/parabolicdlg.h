#ifndef PARABOLICDLG_H
#define PARABOLICDLG_H
#include <qlineedit.h>
#include <qcheckbox.h>
#include "parabolicbase.h"


class ParabolicDlg : public ParabolicBase
{ 
    Q_OBJECT

public:
    ParabolicDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ParabolicDlg();

	inline double lowIntegration() { return m_lowIntegration_edit->text().toDouble(); }
	inline double highIntegration() { return m_highIntegration_edit->text().toDouble(); }
	inline unsigned int eigenNumber() { return m_eigenNumber_edit->text().toUInt(); }
	inline unsigned int numPoints() { return m_numPoints_edit->text().toUInt(); }
	inline double particleMass() { return m_particleMass_edit->text().toDouble(); }
	inline double parabolicCoefficient() { return m_parabolicCoefficient_edit->text().toDouble(); }
	inline bool richardsonExtrapolation() { return m_richardson_checkbox->isChecked(); }
	
	inline void setLowIntegration(double a) { QString s; s.setNum(a); m_lowIntegration_edit->setText(s); }
	inline void setHighIntegration(double a) { QString s; s.setNum(a); m_highIntegration_edit->setText(s); }
	inline void setEigenNumber(unsigned int a) { QString s; s.setNum(a); m_eigenNumber_edit->setText(s); }
	inline void setNumPoints(unsigned int a) { QString s; s.setNum(a); m_numPoints_edit->setText(s); }
	inline void setParticleMass(double a) { QString s; s.setNum(a); m_particleMass_edit->setText(s); }
	inline void setParabolicCoefficient(double a) { QString s; s.setNum(a); m_parabolicCoefficient_edit->setText(s); }
	inline bool checkRichardsonExtrapolation(bool a) { m_richardson_checkbox->setChecked(a); }

signals:
	void signalStartCalc();
	
protected slots:
    void slotTextChanged();
	void slotDoCalc();

};

#endif 
