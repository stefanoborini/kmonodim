#ifndef BARRIER_H
#define BARRIER_H
#include <qlineedit.h>
#include <qcheckbox.h>
#include "barrierbase.h"


class BarrierDlg : public BarrierBase
{ 
    Q_OBJECT

public:
    BarrierDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~BarrierDlg();

	inline double lowIntegration() { return m_lowIntegration_edit->text().toDouble(); }
	inline double highIntegration() { return m_highIntegration_edit->text().toDouble(); }
	inline unsigned int eigenNumber() { return m_eigenNumber_edit->text().toUInt(); }
	inline unsigned int numPoints() { return m_numPoints_edit->text().toUInt(); }
	inline double potentialLowEdge() { return m_potentialLowEdge_edit->text().toDouble(); }
	inline double potentialHighEdge() { return m_potentialHighEdge_edit->text().toDouble(); }
	inline double particleMass() { return m_particleMass_edit->text().toDouble(); }
	inline double extPotential() { return m_extPotential_edit->text().toDouble(); }
	inline double barrierLowEdge() { return m_barrierLowEdge_edit->text().toDouble(); }
	inline double barrierHighEdge() { return m_barrierHighEdge_edit->text().toDouble(); }
	inline double barrierHeight() { return m_barrierHeight_edit->text().toDouble(); }
	inline bool richardsonExtrapolation() { return m_richardson_checkbox->isChecked(); }

	inline void setLowIntegration(double a) { QString s; s.setNum(a); m_lowIntegration_edit->setText(s); }
	inline void setHighIntegration(double a) { QString s; s.setNum(a); m_highIntegration_edit->setText(s); }
	inline void setEigenNumber(unsigned int a) { QString s; s.setNum(a); m_eigenNumber_edit->setText(s); }
	inline void setNumPoints(unsigned int a) { QString s; s.setNum(a); m_numPoints_edit->setText(s); }
	inline void setPotentialLowEdge(double a) { QString s; s.setNum(a); m_potentialLowEdge_edit->setText(s); }
	inline void setPotentialHighEdge(double a) { QString s; s.setNum(a); m_potentialHighEdge_edit->setText(s); }
	inline void setParticleMass(double a) { QString s; s.setNum(a); m_particleMass_edit->setText(s); }
	inline void setExtPotential(double a) { QString s; s.setNum(a); m_extPotential_edit->setText(s); }
	inline void setBarrierLowEdge(double a) { QString s; s.setNum(a); m_barrierLowEdge_edit->setText(s); }
	inline void setBarrierHighEdge(double a) { QString s; s.setNum(a); m_barrierHighEdge_edit->setText(s); }
	inline void setBarrierHeight(double a) { QString s; s.setNum(a); m_barrierHeight_edit->setText(s); }
	inline bool checkRichardsonExtrapolation(bool a) { m_richardson_checkbox->setChecked(a); }

	
signals:
	void signalStartCalc();
	
protected slots:
    void slotTextChanged();
    void slotDoCalc();

};

#endif // BARRIER_H
