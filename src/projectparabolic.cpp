#include <qmessagebox.h>
#include <qdom.h>
#include "mainwindow.h"
#include "parabolicdlg.h"
#include "system.h"
#include "model.h"
#include "potential.h"
#include "projectparabolic.h"
#include "parabolicpotential.h"
#include "error.h"
#include "xmlutils.h"

extern Error *g_error;

// FIXME : check for memory leaks after richardson extrapolation!!!!
//

ProjectParabolic::ProjectParabolic(MainWindow *mw, QString &name ) : Project(mw,name) {
	
	m_dialog = new ParabolicDlg(m_mainWindow);
	QObject::connect(m_dialog, SIGNAL(signalStartCalc()), this, SLOT(slotStartCalc()));
}

ProjectParabolic::~ProjectParabolic() {
	delete m_dialog;
}
	
bool ProjectParabolic::checkValues(bool popup) {
	QString err;
	bool status = false;

    if (m_dialog->lowIntegration() >=  m_dialog->highIntegration()) {
        err = "The Lower Integration parameter is higher or equal the High Integration parameter";
    } else if (m_dialog->numPoints() <= 10) {
        err = "The integration points must be greater than 10 (to give useful results)";
    } else if (m_dialog->numPoints() > 100000) {
        err = "Too many integration points.";
    } else if (m_dialog->eigenNumber() <= 0) {
        err = "Invalid number of eigenvalues requested. Must be greater than zero.";
    } else if (m_dialog->particleMass() <= 0) {
        err = "Invalid particle mass parameter. Must be greater than zero.";
    } else if (m_dialog->parabolicCoefficient() <= 0) {
        err = "Invalid parabolic coefficient. Must be greater than zero.";
    } else {
		status = true;
	}

	if (popup && !status) g_error->error("Error",err);

	return status;
	
}

void ProjectParabolic::slotStartCalc() {

	if (!checkValues(true)) return;
	System *s = createSystem();
	System *r = NULL;
	
	if (m_dialog->richardsonExtrapolation()) {
		r = createRichardsonSystem();
	}
	
    if (!m_model->startCalc(s,r)) {
		g_error->error("Another calculation in progress","The current project is currently busy. Unable to start new thread.\n Wait for the end or start a new project.");
		delete s;
		if (r) delete r;
		return;
	}

}


System *ProjectParabolic::createSystem() {
	System *s = new System( m_dialog->lowIntegration(),
							m_dialog->highIntegration(),
							m_dialog->numPoints(),
    						m_dialog->particleMass(),
    						m_dialog->eigenNumber()
							);
	Potential *p = new ParabolicPotential(s,m_dialog->parabolicCoefficient());
	s->setPotential(p);

	return s;
}

System *ProjectParabolic::createRichardsonSystem() {
	System *s = new System( m_dialog->lowIntegration(),
							m_dialog->highIntegration(),
							m_dialog->numPoints() / 2,
    						m_dialog->particleMass(),
    						m_dialog->eigenNumber()
							);
	Potential *p = new ParabolicPotential(s,m_dialog->parabolicCoefficient());
	s->setPotential(p);

	return s;
}

void ProjectParabolic::XMLSaveSystem(QDomElement &project)	{

	QDomDocument doc = project.ownerDocument();
	QDomElement system = doc.createElement("system");
	project.appendChild(system);
	
	QDomElement elem = doc.createElement("points");
	elem.setAttribute("value",m_system->points());
	system.appendChild(elem);
	
	elem = doc.createElement("lowervalue");
	elem.setAttribute("value",m_system->lowerValue());
	system.appendChild(elem);
	
	elem = doc.createElement("highervalue");
	elem.setAttribute("value",m_system->higherValue());
	system.appendChild(elem);

	elem = doc.createElement("particlemass");
	elem.setAttribute("value",m_system->particleMass());
	system.appendChild(elem);

	// save the potential

	ParabolicPotential *p = (ParabolicPotential*) m_system->potential();

	QDomElement parabolicpotential = doc.createElement("parabolicpotential");
	system.appendChild(parabolicpotential);

	elem = doc.createElement("coefficient");
	elem.setAttribute("value", p->coefficient());
	parabolicpotential.appendChild(elem);

	QDomElement curve = doc.createElement("curve");
	parabolicpotential.appendChild(curve);

	register unsigned int i;
	for (i = 0; i < p->points(); i++) {
		elem = doc.createElement("point");
		elem.setAttribute("value", p->y(i));
		curve.appendChild(elem);
	}
	
	emit signalProgress(40);
	
// save the eigenvalues

	Eigenvalue *e;
	QDomElement eigen;

	for (i = 0; i < m_system->eigenNumber(); i++) {
		e = m_system->eigenvalue(i);

		eigen = doc.createElement("eigenfunction");
		system.appendChild(eigen);
	
		elem = doc.createElement("eigenvalue");
		elem.setAttribute("value",e->eigenvalue());
		eigen.appendChild(elem);
	
		elem = doc.createElement("meanpotential");
		elem.setAttribute("value",e->meanPotential());
		eigen.appendChild(elem);

		elem = doc.createElement("meankinetic");
		elem.setAttribute("value",e->meanKinetic());
		eigen.appendChild(elem);
	
		elem = doc.createElement("meanposition");
		elem.setAttribute("value",e->meanPosition());
		eigen.appendChild(elem);
			
		curve = doc.createElement("curve");
		eigen.appendChild(curve);

		register unsigned int i;
		for (i = 0; i < e->points(); i++) {
			elem = doc.createElement("point");
			elem.setAttribute("value", e->y(i));
			curve.appendChild(elem);
		}
		
	}

}

bool ProjectParabolic::XMLLoadSystem(const QDomElement &project) {
	System *s;
	unsigned int eigenfunctions = 0;
	QString str;

	QDomElement name = XMLUtils::childWithTag(project, "name");
	setName(name.text());

	QDomElement system = XMLUtils::childWithTag(project, "system");
	QDomElement parabolicpotential = XMLUtils::childWithTag(system, "parabolicpotential");
	
	// fill the dialog
	{
		QDomNode node;
		QDomElement elem;
		QLineEdit *edit = NULL;
		QString tag;
		bool status = true;
	
		for (node = system.firstChild(); !node.isNull(); node = node.nextSibling()) {
			elem = node.toElement();
			if (elem.isNull()) continue;
			tag = elem.tagName();
	
			if (tag == "points") m_dialog->m_numPoints_edit->setText(elem.attribute("value"));
			else if (tag == "lowervalue") m_dialog->m_lowIntegration_edit->setText(elem.attribute("value"));
			else if (tag == "highervalue") m_dialog->m_highIntegration_edit->setText(elem.attribute("value"));
			else if (tag == "particlemass") m_dialog->m_particleMass_edit->setText(elem.attribute("value"));
			else if (tag == "eigenfunction") eigenfunctions++; 
			else {}
		}

		str.setNum(eigenfunctions);
		m_dialog->m_eigenNumber_edit->setText(str);
	
		for (node = parabolicpotential.firstChild(); !node.isNull(); node = node.nextSibling()) {
			elem = node.toElement();
			if (elem.isNull()) continue;
			tag = elem.tagName();
			if (tag == "coefficient") m_dialog->m_parabolicCoefficient_edit->setText(elem.attribute("value")); 
			else {}
		
		}

	}
		
	// check it

	if (checkValues(false)) {
		// fill system and potential
		s = createSystem();
	} else
		return false;
	
	// pass to model

	return m_model->XMLLoad(s, system);

}


QString ProjectParabolic::typeName() { return QString("parabolic"); }
QDialog *ProjectParabolic::inputDialog() { return m_dialog; }

#include "projectparabolic.moc"

