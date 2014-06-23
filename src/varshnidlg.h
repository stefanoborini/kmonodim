#ifndef VARSHNIDLG_H
#define VARSHNIDLG_H
#include <qlineedit.h>
#include <qcheckbox.h>
#include "varshnibase.h"


class VarshniDlg : public VarshniBase
{ 
    Q_OBJECT

public:
    VarshniDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~VarshniDlg();

	inline double 		lowIntegration() { return m_lowIntegration_edit->text().toDouble(); }
	inline double 		highIntegration() { return m_highIntegration_edit->text().toDouble(); }
	inline unsigned int eigenNumber() { return m_eigenNumber_edit->text().toUInt(); }
	inline unsigned int numPoints() { return m_numPoints_edit->text().toUInt(); }
	inline double 		particleMass() { return m_particleMass_edit->text().toDouble(); }
	inline double 		de() { return m_de_edit->text().toDouble(); }
	inline double 		alpha() { return m_alpha_edit->text().toDouble(); }
	inline double 		eqDistance() { return m_eqDistance_edit->text().toDouble(); }
	inline unsigned int rotFactor() { return m_rotFactor_edit->text().toUInt(); }
	inline bool 		richardsonExtrapolation() { return m_richardson_checkbox->isChecked(); }
	
	
	inline void 		setLowIntegration(double a) { QString s; s.setNum(a); m_lowIntegration_edit->setText(s); }
	inline void 		setHighIntegration(double a) { QString s; s.setNum(a); m_highIntegration_edit->setText(s); }
	inline void 		setEigenNumber(unsigned int a) { QString s; s.setNum(a); m_eigenNumber_edit->setText(s); }
	inline void 		setNumPoints(unsigned int a) { QString s; s.setNum(a); m_numPoints_edit->setText(s); }
	inline void 		setParticleMass(double a) { QString s; s.setNum(a); m_particleMass_edit->setText(s); }
	inline void 		setDe(double a) { QString s; s.setNum(a); m_de_edit->setText(s); }
	inline double 		setAlpha(double a) { QString s; s.setNum(a); m_alpha_edit->setText(s); }
	inline double 		setEqDistance(double a) { QString s; s.setNum(a); m_eqDistance_edit->setText(s); }
	inline unsigned int setRotFactor(unsigned int a) { QString s; s.setNum(a); m_rotFactor_edit->setText(s); }
	

signals:
	void signalStartCalc();
	
protected slots:
    void slotTextChanged();
	void slotDoCalc();

};

#endif 
