#include <qmessagebox.h>
#include "mainwindow.h"
#include "barrierdlg.h"
#include "system.h"
#include "model.h"
#include "error.h"
#include "xmlutils.h"
#include "barrierpotential.h"
#include "projectbarrier.h"

extern Error *g_error;

ProjectBarrier::ProjectBarrier(MainWindow *mw, QString &name) : Project(mw,name) {
	
	m_dialog = new BarrierDlg(m_mainWindow);
	QObject::connect(m_dialog, SIGNAL(signalStartCalc()), this, SLOT(slotStartCalc()));
}

ProjectBarrier::~ProjectBarrier() {
	delete m_dialog;
}
	
bool ProjectBarrier::checkValues(bool popup) {
	QString err;
	bool status = false;

    if (m_dialog->lowIntegration() >=  m_dialog->highIntegration()) {
        err = "The Lower Integration parameter is higher or equal the High Integration parameter";
    } else if (m_dialog->potentialLowEdge() >=  m_dialog->potentialHighEdge()) {
        err = "The Lower Edge parameter is higher or equal the High Edge parameter";
    } else if (m_dialog->potentialLowEdge() < m_dialog->lowIntegration() || m_dialog->potentialLowEdge() > m_dialog->highIntegration()) {
        err = "The Lower Edge parameter is not in the integration range";
    } else if (m_dialog->potentialHighEdge() < m_dialog->lowIntegration() || m_dialog->potentialHighEdge() > m_dialog->highIntegration()) {
        err = "The High Edge parameter is not in the integration range";
    } else if (m_dialog->extPotential() < 0) {
        err = "The maximal potential paramter must be greater than 0";
    } else if (m_dialog->numPoints() <= 10) {
        err = "The integration points must be greater than 10 (to give useful results)";
    } else if (m_dialog->numPoints() > 100000) {
        err = "Too many integration points";
    } else if (m_dialog->eigenNumber() <= 0) {
        err = "Invalid number of eigenvalues requested. Must be greater than zero.";
    } else if (m_dialog->particleMass() <= 0) {
        err = "Invalid particle mass parameter. Must be greater than zero.";
    } else if (m_dialog->barrierLowEdge() <= m_dialog->potentialLowEdge()) {
		err = "Invalid barrier lower edge. Must be greater than the well lower edge";
	} else if (m_dialog->barrierHighEdge() >= m_dialog->potentialHighEdge()) {
		err = "Invalid barrier higher edge. Must be lower than the well higher edge";
	} else if (m_dialog->barrierLowEdge() >= m_dialog->barrierHighEdge()) {
		err = "The lower edge for the barrier must be lower than the barrier higher edge";
	} else {
		status = true;
	}
	if (popup && !status) g_error->error("Error",err);

	return status;
}

void ProjectBarrier::slotStartCalc() {

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

////////////////////////////////////////////////////////


System *ProjectBarrier::createSystem() {
	System *s = new System( m_dialog->lowIntegration(),
							m_dialog->highIntegration(),
							m_dialog->numPoints(),
    						m_dialog->particleMass(),
    						m_dialog->eigenNumber()
							);
	Potential *p = new BarrierPotential(s,
									m_dialog->potentialLowEdge(),
									m_dialog->potentialHighEdge(),
									m_dialog->extPotential(),
									0.,
									m_dialog->barrierLowEdge(),
									m_dialog->barrierHighEdge(),
									m_dialog->barrierHeight());
	s->setPotential(p);

	return s;
}

System *ProjectBarrier::createRichardsonSystem() {
	System *s = new System( m_dialog->lowIntegration(),
							m_dialog->highIntegration(),
							m_dialog->numPoints() / 2,
    						m_dialog->particleMass(),
    						m_dialog->eigenNumber()
							);
	Potential *p = new BarrierPotential(s,
									m_dialog->potentialLowEdge(),
									m_dialog->potentialHighEdge(),
									m_dialog->extPotential(),
									0.,
									m_dialog->barrierLowEdge(),
									m_dialog->barrierHighEdge(),
									m_dialog->barrierHeight());
	s->setPotential(p);

	return s;
}

void ProjectBarrier::XMLSaveSystem(QDomElement &project)	{

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

	BarrierPotential *p = (BarrierPotential*) m_system->potential();

	QDomElement barrierpotential = doc.createElement("barrierpotential");
	system.appendChild(barrierpotential);

	elem = doc.createElement("lowedge");
	elem.setAttribute("value", p->lowEdge());
	barrierpotential.appendChild(elem);

	elem = doc.createElement("highedge");
	elem.setAttribute("value", p->highEdge());
	barrierpotential.appendChild(elem);

	elem = doc.createElement("highpotential");
	elem.setAttribute("value", p->highPot());
	barrierpotential.appendChild(elem);
	
	elem = doc.createElement("lowpotential");
	elem.setAttribute("value", p->lowPot());
	barrierpotential.appendChild(elem);
	
	elem = doc.createElement("barrierlowedge");
	elem.setAttribute("value", p->barrierLowEdge());
	barrierpotential.appendChild(elem);

	elem = doc.createElement("barrierhighedge");
	elem.setAttribute("value", p->barrierHighEdge());
	barrierpotential.appendChild(elem);
	
	elem = doc.createElement("barrierheight");
	elem.setAttribute("value", p->barrierHeight());
	barrierpotential.appendChild(elem);
	
	QDomElement curve = doc.createElement("curve");
	barrierpotential.appendChild(curve);

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

bool ProjectBarrier::XMLLoadSystem(const QDomElement &project) {
	System *s;
	unsigned int eigenfunctions = 0;
	QString str;

	QDomElement name = XMLUtils::childWithTag(project, "name");
	setName(name.text());

	QDomElement system = XMLUtils::childWithTag(project, "system");
	QDomElement barrierpotential = XMLUtils::childWithTag(system, "barrierpotential");
	
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
	
		for (node = barrierpotential.firstChild(); !node.isNull(); node = node.nextSibling()) {
			elem = node.toElement();
			if (elem.isNull()) continue;
			tag = elem.tagName();
			if (tag == "lowedge") m_dialog->m_potentialLowEdge_edit->setText(elem.attribute("value")); 
			else if (tag == "highedge") m_dialog->m_potentialHighEdge_edit->setText(elem.attribute("value")); 
			else if (tag == "highpotential") m_dialog->m_extPotential_edit->setText(elem.attribute("value")); 
			else if (tag == "barrierlowedge") m_dialog->m_barrierLowEdge_edit->setText(elem.attribute("value"));
			else if (tag == "barrierhighedge") m_dialog->m_barrierHighEdge_edit->setText(elem.attribute("value"));
			else if (tag == "barrierheight") m_dialog->m_barrierHeight_edit->setText(elem.attribute("value"));
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


QString ProjectBarrier::typeName() { return QString("barrier"); }
QDialog *ProjectBarrier::inputDialog() { return m_dialog; }

#include "projectbarrier.moc"

