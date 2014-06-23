#include <malloc.h>
#include <qdom.h>

#include "threadevent.h"
#include "potential.h"
#include "custompotential.h"
#include "eigenvalue.h"
#include "model.h"
#include "system.h"
#include "xmlutils.h"

#include "debug.h"

extern "C" void dstevx_(char *jobz,char *range,int *n,double *d,double *e,double *vl, double *vu,
		int *il,int *iu, double *abstol,int *m,double *w,
		double *z,int *ldz,double *work,int *iwork,int *ifail,int *info);


Model::Model(QObject *parent) : QObject(parent) {
}	

Model::~Model() {
}

bool Model::startCalc(System *s, System *richardson) {

	// this start the calc... when the calc is finished,
	// the model emit the Model::signalDone, which will be received
	// by the Project _generic_ class member slotCheckModel()

	if (running()) return false;

	// now we park the pointer to system class only if the model is currently
	// job free...
	m_system = s;
	m_richardson = richardson;
	m_status = E_Ok;
	start();

	return true;

}


bool Model::XMLLoad(System *sys, const QDomElement &system) {

	register unsigned int i = 0;
	m_system = sys;
	m_status = E_Ok;

	QDomElement eigenfunction;
	QDomNode node = system.firstChild();

	for (node = system.firstChild(); !node.isNull(); node = node.nextSibling()) {
		eigenfunction = node.toElement();
		if (eigenfunction.isNull() || eigenfunction.tagName() != "eigenfunction") continue;
		if (!XMLLoadEigenfunction(eigenfunction,i)) return false;
		i++;
	}


	// check consistency of eigennumbers

	if (m_system->requestedEigenNumber() == i) {
		emit signalDone();
		return true;
	} else return false;


	
}		
			

bool Model::XMLLoadEigenfunction(const QDomElement &eigenfunction, unsigned int index) {
	
	QDomNode node;
	QDomElement elem, curve, point;
	register unsigned int i = 0;
	
	Eigenvalue *e = new Eigenvalue(m_system);

	elem = XMLUtils::childWithTag(eigenfunction,"eigenvalue");
	if (elem.isNull()) goto fail;
	e->setEigenvalue(elem.attribute("value").toDouble());
	e->setTraslateFactor(elem.attribute("value").toDouble());
	e->setScaleFactor(1.);
	
	elem = XMLUtils::childWithTag(eigenfunction,"meanpotential");
	if (elem.isNull()) goto fail;
	e->setMeanPotential(elem.attribute("value").toDouble());
	
	elem = XMLUtils::childWithTag(eigenfunction,"meankinetic");
	if (elem.isNull()) goto fail;
	e->setMeanKinetic(elem.attribute("value").toDouble());

	elem = XMLUtils::childWithTag(eigenfunction,"meanposition");
	if (elem.isNull()) goto fail;
	e->setMeanPosition(elem.attribute("value").toDouble());
	
	curve = XMLUtils::childWithTag(eigenfunction,"curve");
	if (elem.isNull()) goto fail;
	
	for (node = curve.firstChild(); !node.isNull(); node = node.nextSibling()) {
		if (i == m_system->points()) goto fail;
		point = node.toElement();
		if (point.isNull() || point.tagName() != "point") continue;
		e->y(i) = point.attribute("value").toDouble();
		i++;
	}

	if (i != m_system->points()) goto fail; 

	m_system->setEigenvalue(e,index);

	return true;

fail:
	
	delete e;
	return false;
	
}
 

	

// tricky implementation with events, since we need to pass infos between
// the calc thread and the gui thread
void Model::run() {
	ThreadEvent *event;
	
	_debug_enter("in new thread");
	if (!calculateEigenvalues(m_system)) {
		event = new ThreadEvent(THREAD_EVENT_DIAG_FAILED);
		postEvent(this,event);
		return;
	}

	calculateMeanValues(m_system);

	if (m_richardson) { 
		if (!calculateEigenvalues(m_richardson)) {
			event = new ThreadEvent(THREAD_EVENT_DIAG_RICHARDSON_FAILED);
			postEvent(this,event);
			return;
		}
		calculateRichardsonExtrapolation();
		delete m_richardson;
		m_richardson = NULL;
	}

	event = new ThreadEvent(THREAD_EVENT_END_SUCCESS);
	postEvent(this, event);

}


bool Model::event(QEvent *e) {
	ThreadEvent *te;
	
	if (e->type()==THREAD_EVENT) {
		te = (ThreadEvent *)e;
		switch (te->id()) {
			case THREAD_EVENT_END_SUCCESS:
				m_status = E_Ok;
				break;
			case THREAD_EVENT_DIAG_FAILED:
				m_status = E_DiagonalizationFailed;
				break;
			case THREAD_EVENT_DIAG_RICHARDSON_FAILED:
				m_status = E_RichardsonDiagonalizationFailed;
				break;
		}

		// this forces to call Project::slotDone()
		emit signalDone();
		return true;
	}

	return QObject::event(e);
}



	
bool Model::calculateEigenvalues(System *sys) {

	unsigned int i,j;
	bool ret;

// for function dstevx

	char jobz='V'; // computes eigenvalues and eigenvectors
	char rng='I';  // only in a certain range
	int	one = 1;
	double abstol = 1.e-8;
	
	double delta = sys->delta();
	double mass = sys->particleMass();
	unsigned int points = sys->points();
	unsigned int reqEigen = sys->requestedEigenNumber();
	
	double *Hdiag = (double *)malloc(points*sizeof(double));
	double *Hoffdiag = (double *)malloc(points*sizeof(double));

		
// output parameters 
	int neige; // number of eigenvalues found
	double *eigenvalues = (double *)malloc(points*sizeof(double)); // the eigenvalues
	double *eigenvectors = (double *)malloc(sizeof(double)*sys->requestedEigenNumber()*points);
	int *ifail = (int *)malloc(sizeof(int)*points);
	int info;
//	workspace parameters
	
	double *work = (double *)malloc(sizeof(double)*points*5);
	int *iwork = (int *)malloc(sizeof(int)*points*5);
	
//	dimension Hdiag (id1), Hoffdiag(id1)

	double temp1 = -1./(2.*mass*delta*delta);
	double temp2 = 1./(mass*delta*delta);

	for (i=0; i<points; i++) {
		Hoffdiag[i]=temp1;
		Hdiag[i]=temp2+sys->potential()->y(i);
	}	
      
	dstevx_(&jobz,&rng,&(int)points,Hdiag,Hoffdiag,NULL,NULL,
			&one,&(int)reqEigen,&abstol,&neige,eigenvalues,
			eigenvectors,&(int)points,work,iwork,ifail,&info);

	for (i = 0; i < neige; i++) qDebug("eigenvalue %i : %10.20g",i,eigenvalues[i]);

	if (!info) { 
		for (i = 0; i < neige; i++) {
			Eigenvalue *e = new Eigenvalue(sys);
			e->setEigenvalue(eigenvalues[i]);

			for (j = 0; j < points; j++) {
				e->y(j) = (*(eigenvectors+i*points+j));
			}
			
			e->normalize();

			// check the sanity of the eigenfunction
			// integrating it in the first 10% of the integration range.
			// if the obtained value is under a certain limit, the eigenfunction
			// is considered good, otherwise it's marked as "invalid"
			
			double interval = ( sys->higherValue() - sys->lowerValue() ) / 10;
			double sum=0.;
				
			for (j = 0; j < points; j++) {
				if (sys->x(j) > ( sys->lowerValue() + interval ) && sys->x(j) < ( sys->higherValue() - interval )) continue;
				sum += e->y(j) * e->y(j);
			}
			sum*=delta;
			e->setHasWrongIntegrationLimits ( (sum > 1.e-8) );
			sys->setEigenvalue(e,i);
		}	
	}
	
	// free ram
	// 
	
	free(Hdiag);
	free(Hoffdiag);
	free(eigenvalues);
	free(eigenvectors);
	free(ifail);
	free(work);
	free(iwork);

	return (!info);

}


void Model::calculateMeanValues(System *sys) {
	Eigenvalue *e;
	double sum;
	register unsigned int i,j;

	for (i = 0; i < sys->eigenNumber(); i++) {
		e = sys->eigenvalue(i);
		sum=0.;
		for (j = 0; j < sys->points(); j++) sum += e->y(j) * e->y(j) * sys->potential()->y(j);
		sum *= sys->delta();
		e->setMeanPotential(sum);

		sum = 0.;
		for (j = 0; j < sys->points(); j++) sum += e->y(j)*e->y(j) * sys->x(j);
		sum *= sys->delta();
		e->setMeanPosition(sum);

		sum = 0.;
		for (j = 1; j < sys->points() - 1; j++) sum += e->y(j) * ( e->y(j+1) + e->y(j-1) - 2 * e->y(j) );
		sum *= 1 / ( - 2 * sys->particleMass() * sys->delta());
		e->setMeanKinetic(sum);

	}
	
}

void Model::calculateRichardsonExtrapolation() {

	register unsigned int i;

	// XXX : copy constructor & co. should be more elegant
	
//	System *redsys = new System(sys->lowerValue(),sys->higherValue(),sys->points()/2,sys->particleMass(),sys->requestedEigenNumber());
//	Potential *p = new CustomPotential(redsys, sys->potential());
//	redsys->setPotential(p);
//	calculateEigenvalues(redsys);

	Eigenvalue *e, *ered;
	
	double alpha = m_richardson->delta() / m_system->delta();
	double alpha2 = alpha*alpha;

	for (i = 0; i < m_system->eigenNumber(); i++) {
		e = m_system->eigenvalue(i);
		ered = m_richardson->eigenvalue(i);
		e->setExtrapolatedEigenvalue( (alpha2*e->eigenvalue() - ered->eigenvalue()) / (alpha2 - 1) );
	}

	m_system->setHasExtrapolation(true);

}


		
#include "model.moc"

