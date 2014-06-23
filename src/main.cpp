#include <kapp.h>
#include <stdio.h>

#include "error.h"
#include "mainwindow.h"

Error *g_error;

int main( int argc, char ** argv ) {
    KApplication a( argc, argv, "application" );
    MainWindow *mainwindow = new MainWindow("main");
    mainwindow->setCaption( "Quantum Chemistry - Simple monodimensional solver" );
	g_error = new Error(mainwindow);

	QWidget *d = QApplication::desktop();
	
	mainwindow->setGeometry(0,0,d->width(),d->height());
		
    mainwindow->show();
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    a.exec();

	delete g_error;
}
