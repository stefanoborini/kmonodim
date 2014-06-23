#ifndef PROJECT_H
#define PROJECT_H

#include <qobject.h>
#include "model.h"

class MainWindow;
class Model;
class System;
class Palette;
class Plot;
class EigenListView;
class Integral;

class Project : public QObject {
	Q_OBJECT
public:
	
	enum ProjectType {	SquareWell = 1,
						Barrier,
						Parabolic,
						Morse,
						Varshni
					};

	Project(MainWindow *mw, QString name = QString::null);
	~Project();

	// get internal data
	inline Plot *			plot() { return m_plot; }
	inline EigenListView *	eigenListView() { return m_eigenList; }
	inline System *			system() { return m_system; }
	inline Palette *		palette() { return m_palette; }
	virtual QDialog *		inputDialog() = 0;
	QDialog *				integralDialog();


	// various check functions
	inline bool 			isRunning(void) const { return m_model->running(); }
	inline bool 			hasValidData(void) const { return (m_system != NULL); }

	// generic interface
	virtual ProjectType 	type() = 0;
	virtual QString			typeName() = 0;

	inline const QString &	name(void) const { return m_name; }
	void 					setName(const QString &name);
	inline const QString &	filename(void) const { return m_filename; }
	void 					setFilename(const QString &filename);
	
	// load/save and correlated checking
	void 					XMLSave(QDomElement &elem);
	virtual bool 			XMLLoad(const QDomElement &project);

protected slots:

	virtual void 			slotStartCalc(void) = 0;
	void 					slotCheckModel();
	
signals:
	void 					signalDataAvailable(Project *);
	void					signalProgress(int);

protected:

	virtual bool 			checkValues(bool popup) = 0;

	virtual bool 			XMLLoadSystem(const QDomElement &project) = 0;
	bool 					XMLLoadPalette(const QDomElement &project);

	void 					XMLSavePalette(QDomElement &project);
	virtual void 			XMLSaveSystem(QDomElement &project) = 0;

	MainWindow *			m_mainWindow;	
	Plot *					m_plot;
	Model *					m_model;
	Palette *				m_palette;
	EigenListView *			m_eigenList;
	Integral *				m_integral;
	System *				m_system;

	QString					m_name;
	QString					m_filename;

};


#endif
