#ifndef MODEL_H
#define MODEL_H

#define QT_THREAD_SUPPORT 

#include <qobject.h>
#include <qthread.h>
#include <qlist.h>
#include "eigenvalue.h"
#include "potential.h"

class System;

class Model : public QObject , public QThread {
	Q_OBJECT;
public:

	enum Status { 	E_Ok = 0, 
					E_WrongIntegrationLimits, 
					E_DiagonalizationFailed,
					E_RichardsonDiagonalizationFailed };
	
	Model(QObject *parent);
	~Model();

	bool startCalc(System *sys, System *richardson = NULL);
	bool XMLLoad(System *, const QDomElement &);

	Status status() { return m_status; } 
	
	System *currentSystem() { return m_system; }
	
signals:
	void signalDone();
	
protected: // members

	virtual bool event(QEvent *e);

	// other thread
	virtual void run();
	bool calculateEigenvalues(System *);
	void calculateMeanValues(System *);	
	void calculateRichardsonExtrapolation();
//	bool checkIntegrationLimits();

	bool XMLLoadEigenfunction(const QDomElement &eigenfunction, unsigned int index);

protected: // variables
	
	System *m_system;
	System *m_richardson;
	Status m_status;
};

#endif
