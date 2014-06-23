#ifndef PROJECTMORSE_H
#define PROJECTMORSE_H

#include "project.h"

class System;
class MorseDlg;
class QString;

class ProjectMorse : public Project {
	Q_OBJECT
public:
	ProjectMorse(MainWindow *mw, QString &name );
	~ProjectMorse();

	inline virtual Project::ProjectType type() { return Project::Morse; }
	inline virtual QString 				typeName();
	inline virtual QDialog * 			inputDialog();

protected:
	
	virtual bool 		checkValues(bool popup);
	virtual System *	createSystem(void);
	virtual System *	createRichardsonSystem(void);
	virtual bool 		XMLLoadSystem(const QDomElement &project);
	virtual void 		XMLSaveSystem(QDomElement &project);

	MorseDlg *			m_dialog;

protected slots:
	virtual void 		slotStartCalc();

};

#endif
