#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <qobject.h>
#include <qstring.h>

class MainWindow;
class Project;
class QDomElement;

class FileManager : public QObject {
	Q_OBJECT;
public:
	enum Status { Ok = 0, FileNotFound, NoReadPerms, ParseError, InvalidProjectType, NoWritePerms, InvalidXMLData };
	FileManager(MainWindow *parent);

	Project *load(const QString &filename);
	bool save(Project *p, const QString &filename);

	Status status() { return m_status; }

protected:
	MainWindow *m_mainWindow;

	Status m_status;
	
	Project *allocateProject(QDomElement &elem);

protected slots:
	void		slotProjectProgress(int);
	
signals:
	void		signalProgress(int);

};

#endif
