bin_PROGRAMS = kmonodim
kmonodim_SOURCES = main.cpp \
		model.cpp \
		curve.cpp \
		mainwindow.cpp \
		eigenvalue.cpp \
		system.cpp \
		color.cpp \
		project.cpp \
		projectsquarewell.cpp \
		projectbarrier.cpp \
		projectparabolic.cpp \
		projectmorse.cpp \
		projectvarshni.cpp \
		palette.cpp \
		arrowpad.cpp \
		arrowpadbase.cpp \
		eigenlistviewbase.cpp \
		eigenlistview.cpp \
		mylistviewitem.cpp \
		plot.cpp \
		squarewelldlg.cpp \
		squarewellbase.cpp \
		squarewellpotential.cpp \
		barrierdlg.cpp \
		barrierbase.cpp \
		barrierpotential.cpp \
		parabolicdlg.cpp \
		parabolicbase.cpp \
		parabolicpotential.cpp \
		morsedlg.cpp \
		morsebase.cpp \
		morsepotential.cpp \
		varshnidlg.cpp \
		varshnibase.cpp \
		varshnipotential.cpp \
		xmlutils.cpp \
		filemanager.cpp \
		integral.cpp \
		integralbase.cpp \
		custompotential.cpp


noinst_HEADERS = eigenvalue.h \
		model.h \
		curve.h \
		potential.h \
		threadevent.h \
		mainwindow.h \
		system.h \
		color.h \
		project.h \
		projectsquarewell.h \
		projectbarrier.h \
		projectparabolic.h \
		projectmorse.h \
		projectvarshni.h \
		palette.h \
		arrowpad.h \
		arrowpadbase.h \
		eigenlistviewbase.h \
		eigenlistview.h \
		mylistviewitem.h \
		plot.h \
		squarewelldlg.h \
		squarewellbase.h \
		squarewellpotential.h \
		barrierdlg.h \
		barrierbase.h \
		barrierpotential.h \
		parabolicdlg.h \
		parabolicbase.h \
		parabolicpotential.h \
		morsedlg.h \
		morsebase.h \
		morsepotential.h \
		xmlutils.h \
		filemanager.h \
		integral.h \
		integralbase.h \
		custompotential.h


squarewellbase.h: squarewelldlg.ui
	$(UIC_PATH) squarewelldlg.ui -o squarewellbase.h
squarewellbase.cpp: squarewellbase.h squarewelldlg.ui
	$(UIC_PATH) -impl squarewellbase.h squarewelldlg.ui -o squarewellbase.cpp
barrierbase.h: barrierdlg.ui
	$(UIC_PATH) barrierdlg.ui -o barrierbase.h
barrierbase.cpp: barrierbase.h barrierdlg.ui
	$(UIC_PATH) -impl barrierbase.h barrierdlg.ui -o barrierbase.cpp
parabolicbase.h: parabolicdlg.ui
	$(UIC_PATH) parabolicdlg.ui -o parabolicbase.h
parabolicbase.cpp: parabolicbase.h parabolicdlg.ui
	$(UIC_PATH) -impl parabolicbase.h parabolicdlg.ui -o parabolicbase.cpp
morsebase.h: morsedlg.ui
	$(UIC_PATH) morsedlg.ui -o morsebase.h
morsebase.cpp: morsebase.h morsedlg.ui
	$(UIC_PATH) -impl morsebase.h morsedlg.ui -o morsebase.cpp
varshnibase.h: varshnidlg.ui
	$(UIC_PATH) varshnidlg.ui -o varshnibase.h
varshnibase.cpp: varshnibase.h varshnidlg.ui
	$(UIC_PATH) -impl varshnibase.h varshnidlg.ui -o varshnibase.cpp
arrowpadbase.h: arrowpad.ui
	$(UIC_PATH) arrowpad.ui -o arrowpadbase.h
arrowpadbase.cpp: arrowpad.ui
	$(UIC_PATH) -impl arrowpadbase.h arrowpad.ui -o arrowpadbase.cpp
eigenlistviewbase.h: eigenlistview.ui
	$(UIC_PATH) eigenlistview.ui -o eigenlistviewbase.h
eigenlistviewbase.cpp: eigenlistview.ui
	$(UIC_PATH) -impl eigenlistviewbase.h eigenlistview.ui -o eigenlistviewbase.cpp
integralbase.h: integral.ui
	$(UIC_PATH) integral.ui -o integralbase.h
integralbase.cpp: integral.ui
	$(UIC_PATH) -impl integralbase.h integral.ui -o integralbase.cpp

%.moc: %.h
	$(MOC_PATH) $< -o $@

mainwindow.cpp: arrowpadbase.h mainwindow.moc
squarewelldlg.cpp: squarewelldlg.moc squarewellbase.moc
barrierdlg.cpp: barrierdlg.moc barrierbase.moc
parabolicdlg.cpp: parabolicdlg.moc parabolicbase.moc
morsedlg.cpp: morsedlg.moc morsebase.moc
varshnidlg.cpp: varshnidlg.moc varshnibase.moc
model.cpp: model.moc
project.cpp: project.moc integralbase.h
projectsquarewell.cpp: projectsquarewell.moc squarewellbase.h
projectbarrier.cpp: projectbarrier.moc barrierbase.h
projectparabolic.cpp: projectparabolic.moc parabolicbase.h
projectmorse.cpp: projectmorse.moc morsebase.h
projectvarshni.cpp: projectvarshni.moc varshnibase.h
plot.cpp: plot.moc
arrowpad.cpp: arrowpad.moc arrowpadbase.moc
filemanager.cpp: filemanager.moc
eigenlistview.cpp: eigenlistview.moc eigenlistviewbase.moc
palette.cpp: palette.moc
integral.cpp: integral.moc integralbase.moc

CLEANFILES = *.moc squarewellbase.h squarewellbase.cpp barrierbase.h barrierbase.cpp \
                morsebase.h morsebase.cpp parabolicbase.h parabolicbase.cpp \
                integralbase.h integralbase.cpp arrowpadbase.cpp arrowpadbase.h \
                varshnibase.h varshnibase.cpp
