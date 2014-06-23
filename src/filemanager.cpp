#include <qfile.h>
#include <qfileinfo.h>
#include <qdom.h>
#include <kapp.h>

#include "xmlutils.h"
#include "projectsquarewell.h"
#include "projectbarrier.h"
#include "projectparabolic.h"
#include "projectmorse.h"
#include "projectvarshni.h"
#include "filemanager.h"
#include "mainwindow.h"

FileManager::FileManager(MainWindow *parent) : QObject(parent) {

	m_mainWindow = parent;
}

bool FileManager::save(Project *p, const QString &filename) {
	
	m_status = Ok;
	
	QFile f(filename);
	
	if (! f.open(IO_WriteOnly)) {
		m_status = NoWritePerms;
		return false;
	}

	QDomDocument doc("kmonodim");
	QDomElement root = doc.createElement("kmonodim");
	doc.appendChild(root);

	QObject::connect(p,SIGNAL(signalProgress(int)), this, SLOT(slotProjectProgress(int)));
	p->XMLSave(root);
	QObject::disconnect(p,SIGNAL(signalProgress(int)), this, SLOT(slotProjectProgress(int)));

	QString out = doc.toString();
	f.writeBlock((const char *)out, out.length());
	f.close();

	emit signalProgress(100);

	return true;
}


Project *FileManager::load(const QString &filename) {

	QDomDocument doc( "kmonodim" );
	m_status = Ok;
    QFile f( filename );
	
	if ( !f.open( IO_ReadOnly ) ) {
		QFileInfo info( f );
		if (! info.exists()) m_status = FileNotFound;
		else if ( ! info.isReadable()) m_status = NoReadPerms;
		f.close();
		return NULL;
	}


	if ( !doc.setContent( &f ) ) {
		m_status = ParseError;
		f.close();
		return NULL;
	}

	f.close();

	// now it's all in doc

	QDomElement root = doc.documentElement();
	Project *p = allocateProject(root);

	if (!p) return NULL;
	
	if (p->XMLLoad(root)) {
		m_status = Ok;
		return p;
	} else {	
		delete p;
		m_status = InvalidXMLData;
		return NULL;
	}

}


Project *FileManager::allocateProject(QDomElement &elem) {
	Project *p;
	bool ok;

	QString type = XMLUtils::attributeValue(elem, "project", "type");
	QString name = "loading...";

	if (type == "squarewell") {
		p = new ProjectSquareWell(m_mainWindow,name);
	} else if (type == "barrier") {
		p = new ProjectBarrier(m_mainWindow,name);
	} else if (type == "parabolic") {
		p = new ProjectParabolic(m_mainWindow,name);
	} else if (type == "morse") {
		p = new ProjectMorse(m_mainWindow,name);
	} else if (type == "varshni") {
		p = new ProjectVarshni(m_mainWindow,name);
	} else {	
		m_status = InvalidProjectType;
		p = NULL;
	}

	return p;
}

/* while the project report a progress from 0 to 100, the filemanager
 * report from 0 to 90, and the final 10% is saving the file
 */
void FileManager::slotProjectProgress(int value) {
	
	int cur =(int)(value * 0.8 + 0);
	qDebug("emit signalProgress %d",cur);
	emit signalProgress(cur);
}



#include "filemanager.moc"
