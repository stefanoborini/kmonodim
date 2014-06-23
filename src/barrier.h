#ifndef BARRIER_H
#define BARRIER_H
#include <qlineedit.h>
#include "barrierbase.h"


class BarrierDlg : public BarrierBase
{ 
    Q_OBJECT

public:
    BarrierDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~BarrierDlg();

	inline double getLowIntegration() { return m_lowIntegration_edit->text().toDouble(); }
	inline double getHighIntegration() { return m_highIntegration_edit->text().toDouble(); }
	inline unsigned int getEigenNumber() { return m_eigenNumber_edit->text().toUInt(); }
	inline unsigned int getNumPoints() { return m_numPoints_edit->text().toUInt(); }
	inline double getLowEdge() { return m_lowEdge_edit->text().toDouble(); }
	inline double getHighEdge() { return m_highEdge_edit->text().toDouble(); }
	inline double getParticleMass() { return m_particleMass_edit->text().toDouble(); }
	inline double getMaxPotential() { return m_maxPotential_edit->text().toDouble(); }
	inline double getBarrierLowEdge() { return m_barrierLowEdge_edit->text().toDouble(); }
	inline double getBarrierHighEdge() { return m_barrierHighEdge_edit->text().toDouble(); }
	inline double getBarrierHeight() { return m_barrierHeight_edit->text().toDouble(); }
	
signals:
	void signalStartCalc();
	
protected slots:
    void slotTextChanged();
    void slotDoCalc();

};

#endif // BARRIER_H
