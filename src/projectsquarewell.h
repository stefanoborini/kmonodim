#ifndef PROJECTSQUAREWELL_H
#define PROJECTSQUAREWELL_H

#include "project.h"

class System;
class SquareWellDlg;
class QString;

class ProjectSquareWell : public Project {
	Q_OBJECT
public:
	ProjectSquareWell(MainWindow *mw, QString &name );
	~ProjectSquareWell();

	inline virtual Project::ProjectType type() { return Project::SquareWell; }
	inline virtual QString 				typeName();
	inline virtual QDialog * 			inputDialog();

protected:
	
	virtual bool 		checkValues(bool popup);
	virtual System *	createSystem(void);
	virtual System *	createRichardsonSystem(void);
	virtual bool 		XMLLoadSystem(const QDomElement &project);
	virtual void 		XMLSaveSystem(QDomElement &project);

	SquareWellDlg *		m_dialog;

protected slots:
	virtual void 		slotStartCalc();

};

#endif
