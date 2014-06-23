#ifndef PROJECTVARSHNI_H
#define PROJECTVARSHNI_H

#include "project.h"

class System;
class VarshniDlg;
class QString;

class ProjectVarshni : public Project {
	Q_OBJECT
public:
	ProjectVarshni(MainWindow *mw, QString &name );
	~ProjectVarshni();

	inline virtual Project::ProjectType type() { return Project::Varshni; }
	inline virtual QString 				typeName();
	inline virtual QDialog * 			inputDialog();

protected:
	
	virtual bool 		checkValues(bool popup);
	virtual System *	createSystem(void);
	virtual System *	createRichardsonSystem(void);
	virtual bool 		XMLLoadSystem(const QDomElement &project);
	virtual void 		XMLSaveSystem(QDomElement &project);

	VarshniDlg *			m_dialog;

protected slots:
	virtual void 		slotStartCalc();

};

#endif
