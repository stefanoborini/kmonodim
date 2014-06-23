AC_DEFUN(AC_SS_FIND_QWT_LIBRARY_DIR,
[
	AC_ARG_WITH(qwt-library-dir,[  --with-qwt-library-dir      Path to the Qwt Widget set library],SS_QWT_LIBRARY_DIR="$withval",SS_QWT_LIBRARY_DIR="NOTGIVEN")
	if test "$SS_QWT_LIBRARY_DIR" = "NOTGIVEN"; then
		unset SS_QWT_LIBRARY_DIR

		AC_MSG_CHECKING(for the Qwt widget library)
		ss_qwt_library_test_dirs="/lib /usr/lib /usr/local/lib /usr/qwt/lib /usr/local/qwt/lib /usr/X11R6/lib /usr/lib/qwt/lib /usr/lib/qwt /usr/local/lib/qwt/lib"

		AC_SS_FIND_FILE_PATH(libqwt.so,$ss_qwt_library_test_dirs,SS_QWT_LIBRARY_DIR)

		if test "$SS_QWT_LIBRARY_DIR" = "FAILED"; then
			AC_MSG_RESULT("FAILED")
			AC_SS_MESSAGE("CONFIGURE ERROR: cannot find qwt library")
			AC_MSG_ERROR(["This was a fatal one...aborting"])
		else
			AC_MSG_RESULT(found in $SS_QWT_LIBRARY_DIR)
		fi
	else
		AC_MSG_RESULT(using user supplied path for the Qt library $SS_QWT_LIBRARY_DIR)
	fi
	LIBS="$LIBS -L$SS_QWT_LIBRARY_DIR -lqwt"
])

AC_DEFUN(AC_SS_FIND_QWT_INCLUDE_DIR,
[
	AC_ARG_WITH(qwt-include-dir,[  --with-qwt-include-dir      Path to the Qwt Widget set include files],SS_QWT_INCLUDE_DIR="$withval",SS_QWT_INCLUDE_DIR="NOTGIVEN")
	if test "$SS_QWT_INCLUDE_DIR" = "NOTGIVEN"; then
 		unset SS_QWT_INCLUDE_DIR
 
 		AC_MSG_CHECKING(for the Qwt widget include files)
 		ss_qwt_include_test_dirs="/usr/include /usr/local/include /usr/include/qwt/ /usr/include/qwt/include /usr/X11R6/include /usr/local/qwt/include/ /usr/local/include/qwt"
 
 		AC_SS_FIND_FILE_PATH(qwt_plot.h,$ss_qwt_include_test_dirs,SS_QWT_INCLUDE_DIR)
 
 		if test "$SS_QWT_INCLUDE_DIR" = "FAILED"; then
 			AC_MSG_RESULT("FAILED")
 			AC_SS_MESSAGE("CONFIGURE ERROR: cannot find qwt library")
 			AC_MSG_ERROR(["This was a fatal one...aborting"])
 		else
 			AC_MSG_RESULT(found in $SS_QWT_INCLUDE_DIR)
 		fi
 	else
 		AC_MSG_RESULT(using user supplied path for the Qt library $SS_QWT_INCLUDE_DIR)
 	fi
 	CPPFLAGS="$CPPFLAGS -I$SS_QWT_INCLUDE_DIR"
])

AC_DEFUN(AC_SS_CHECK_QWT_VERSION,
[
	AC_MSG_CHECKING([for old (<0.4) Qwt library version])
	AC_TRY_COMPILE([
				#include <qapplication.h>
				#include <qwt_math.h>
				#include <qwt_plot.h>
				],[
				int argc;
				char **argv;
				QApplication a(argc,argv);
				QwtPlot *p = new QwtPlot(NULL,"a");
				double hy = p->axisScale(QwtPlot::yLeft).hBound();
				a.exec();
				],
				eval "qwt_old=yes",
				eval "qwt_old=no"
	)
	
	if test "$qwt_old" = "yes"; then
		AC_MSG_RESULT([old qwt release])
		AC_DEFINE(HAVE_OLD_QWT)
	else
		AC_MSG_RESULT([recent qwt release])
	fi
])
