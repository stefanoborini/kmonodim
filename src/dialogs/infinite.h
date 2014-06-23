#ifndef INFINITEDLG_H
#define INFINITEDLG_H
#include "infinitebase.h"


class InfiniteDlg : public InfiniteBase
{ 
    Q_OBJECT

public:
    InfiniteDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~InfiniteDlg();

	inline unsigned int getEigenNumber() { return m_eigenNumber_edit->text().toUInt(); }
	inline unsigned int getNumPoints() { return m_numPoints_edit->text().toUInt(); }
	inline double getLowEdge() { return m_lowEdge_edit->text().toDouble(); }
	inline double getHighEdge() { return m_highEdge_edit->text().toDouble(); }
	inline double getParticleMass() { return m_particleMass->text().toDouble(); }

signals:
	void signalStartCalc();
	
protected slots:
    void slotTextChanged();
    void slotDoCalc();

};

#endif 
