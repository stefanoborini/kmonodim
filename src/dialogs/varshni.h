#ifndef VARSHNI_H
#define VARSHNI_H
#include "varshnibase.h"

class VarshniDlg : public VarshniBase
{ 
    Q_OBJECT

public:
    VarshniDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~VarshniDlg();

	inline double getLowIntegration() { return m_lowIntegration_edit->text().toDouble(); }
	inline double getHighIntegration() { return m_highIntegration_edit->text().toDouble(); }
	inline unsigned int getEigenNumber() { return m_eigenNumber_edit->text().toUInt(); }
	inline unsigned int getNumPoints() { return m_numPoints_edit->text().toUInt(); }
	inline double getLowEdge() { return m_lowEdge_edit->text().toDouble(); }
	inline double getHighEdge() { return m_highEdge_edit->text().toDouble(); }
	inline double getParticleMass() { return m_particleMass->text().toDouble(); }
	inline double getMaxPotential() { return m_maxPotential_edit->text().toDouble(); }
	inline double getDe() { return m_de_edit->text().toDouble(); }
	inline double getAlpha() { return m_alpha_edit->text().toDouble(); }
	inline unsigned int getRotFactor() { return m_rotFactor_edit->text().toUInt(); }
	inline double getEqDistance() { return m_eqDistance_edit->text().toDouble(); }

signals:
	void signalStartCalc();
	
protected slots:
    void slotDoCalc();
    void slotTextChanged();

};

#endif // VARSHNI_H


