#ifndef PROJECTBARRIER_H
#define PROJECTBARRIER_H

#include "project.h"

class System;
class BarrierDlg;
class QString;

class ProjectBarrier : public Project {
	Q_OBJECT
public:
	ProjectBarrier(MainWindow *mw, QString &name );
	~ProjectBarrier();

	inline virtual Project::ProjectType type() { return Project::Barrier; }
	inline virtual QString 				typeName();
	inline virtual QDialog *			inputDialog();

protected:
	
	virtual bool 		checkValues(bool popup);
	virtual System *	createSystem(void);
	virtual System *	createRichardsonSystem(void);
	virtual bool 		XMLLoadSystem(const QDomElement &project);
	virtual void 		XMLSaveSystem(QDomElement &project);

	BarrierDlg *		m_dialog;

protected slots:
	virtual void 		slotStartCalc();

};

#endif
