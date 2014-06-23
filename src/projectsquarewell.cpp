#include <qmessagebox.h>
#include <qdom.h>
#include "mainwindow.h"
#include "squarewelldlg.h"
#include "system.h"
#include "model.h"
#include "potential.h"
#include "projectsquarewell.h"
#include "squarewellpotential.h"
#include "error.h"
#include "xmlutils.h"

extern Error *g_error;

// check the game with the system...
// this code works in this way: the project base class is the parent class for
// every project. it holds a lot of stuff. in the way i'll comment how it works.
// it's not so complex, but tricky

ProjectSquareWell::ProjectSquareWell(MainWindow *mw, QString &name ) : Project(mw,name) {
	
	// this dialog is different on a per-project base, so we need to create
	// a different one for each project
	m_dialog = new SquareWellDlg(m_mainWindow);
	QObject::connect(m_dialog, SIGNAL(signalStartCalc()), this, SLOT(slotStartCalc()));
}

ProjectSquareWell::~ProjectSquareWell() {
	delete m_dialog;
}
	
// checks the correctness of the values held by the dialog, returns true if
// ok, else false and an error message if something is wrong.
bool ProjectSquareWell::checkValues(bool popup) {
	QString err;
	bool status = false;

    if (m_dialog->lowIntegration() >=  m_dialog->highIntegration()) {
        err = "The Lower Integration parameter is higher or equal the High Integration parameter";
    } else if (m_dialog->potentialLowEdge() >= m_dialog->potentialHighEdge()) {
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
        err = "Too many integration points.";
    } else if (m_dialog->eigenNumber() <= 0) {
        err = "Invalid number of eigenvalues requested. Must be greater than zero.";
    } else if (m_dialog->particleMass() <= 0) {
        err = "Invalid particle mass parameter. Must be greater than zero.";
    } else {
		status = true;
	}

	if (popup && !status) g_error->error("Error",err);

	return status;
	
}

// here we start the calc...
void ProjectSquareWell::slotStartCalc() {

	if (!checkValues(true)) return;

	// ok.. now start the game... we create a new temporary system, setting on it
	// all the input parameters. System is a package-class which holds input data
	// and output data. it's passed to the calc factory, the model, when the calc
	// start. However, it's not granted the model is effectively resting.

	System *s = createSystem();
	System *r = NULL;
	
	if (m_dialog->richardsonExtrapolation()) {
		r = createRichardsonSystem();
	}

	//   startCalc return false if the model is working on another system.
	//   in this case, we ask to wait, and discard the system we built.
	//   a smarter code should span another project, but i don't care to be
	//   too much smarter, since i want to preserve that little mental sanity i
	//   currently have. now let's go to see Model::startCalc()

	// new: r is the richardson system. Nothing more than a carbon copy system
	// with half of the points. We pass it to the model

    if (!m_model->startCalc(s,r)) {
		g_error->error("Another calculation in progress","The current project is currently busy. Unable to start new thread.\n Wait for the end or start a new project.");
		delete s;
		if (r) delete r;
		return;
	}

}


System *ProjectSquareWell::createSystem() {
	System *s = new System( m_dialog->lowIntegration(),
							m_dialog->highIntegration(),
							m_dialog->numPoints(),
    						m_dialog->particleMass(),
    						m_dialog->eigenNumber()
							);
	Potential *p = new SquareWellPotential(s,m_dialog->potentialLowEdge(),m_dialog->potentialHighEdge(),m_dialog->extPotential(),0.);
	s->setPotential(p);

	return s;
}

System *ProjectSquareWell::createRichardsonSystem() {
	System *s = new System( m_dialog->lowIntegration(),
							m_dialog->highIntegration(),
							m_dialog->numPoints() / 2,
    						m_dialog->particleMass(),
    						m_dialog->eigenNumber()
							);
	Potential *p = new SquareWellPotential(s,m_dialog->potentialLowEdge(),m_dialog->potentialHighEdge(),m_dialog->extPotential(),0.);
	s->setPotential(p);

	return s;
}



void ProjectSquareWell::XMLSaveSystem(QDomElement &project)	{

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

	SquareWellPotential *p = (SquareWellPotential*) m_system->potential();

	QDomElement squarewellpotential = doc.createElement("squarewellpotential");
	system.appendChild(squarewellpotential);

	elem = doc.createElement("lowedge");
	elem.setAttribute("value", p->lowEdge());
	squarewellpotential.appendChild(elem);

	elem = doc.createElement("highedge");
	elem.setAttribute("value", p->highEdge());
	squarewellpotential.appendChild(elem);

	elem = doc.createElement("highpotential");
	elem.setAttribute("value", p->highPot());
	squarewellpotential.appendChild(elem);
	
	elem = doc.createElement("lowpotential");
	elem.setAttribute("value", p->lowPot());
	squarewellpotential.appendChild(elem);
	
	QDomElement curve = doc.createElement("curve");
	squarewellpotential.appendChild(curve);

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

bool ProjectSquareWell::XMLLoadSystem(const QDomElement &project) {
	System *s;
	unsigned int eigenfunctions = 0;
	QString str;

	QDomElement name = XMLUtils::childWithTag(project, "name");
	setName(name.text());

	QDomElement system = XMLUtils::childWithTag(project, "system");
	QDomElement squarewellpotential = XMLUtils::childWithTag(system, "squarewellpotential");
	
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
	
		for (node = squarewellpotential.firstChild(); !node.isNull(); node = node.nextSibling()) {
			elem = node.toElement();
			if (elem.isNull()) continue;
			tag = elem.tagName();
			if (tag == "lowedge") m_dialog->m_potentialLowEdge_edit->setText(elem.attribute("value")); 
			else if (tag == "highedge") m_dialog->m_potentialHighEdge_edit->setText(elem.attribute("value")); 
			else if (tag == "highpotential") m_dialog->m_extPotential_edit->setText(elem.attribute("value")); 
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


QString ProjectSquareWell::typeName() { return QString("squarewell"); }
QDialog *ProjectSquareWell::inputDialog() { return m_dialog; }

#include "projectsquarewell.moc"

