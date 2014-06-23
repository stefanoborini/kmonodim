#ifndef PROJECTPARABOLIC_H
#define PROJECTPARABOLIC_H

#include "project.h"

class System;
class ParabolicDlg;
class QString;

class ProjectParabolic : public Project {
	Q_OBJECT
public:
	ProjectParabolic(MainWindow *mw, QString &name );
	~ProjectParabolic();

	inline virtual Project::ProjectType type() { return Project::Parabolic; }
	inline virtual QString typeName();
	inline virtual QDialog * inputDialog();

protected:
	
	virtual bool checkValues(bool popup);
	virtual System *createSystem(void);
	virtual System *createRichardsonSystem(void);
	virtual bool XMLLoadSystem(const QDomElement &project);
	virtual void XMLSaveSystem(QDomElement &project);

	ParabolicDlg *m_dialog;

protected slots:
	virtual void slotStartCalc();

};

#endif
