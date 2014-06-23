#### search qt
#### 

AC_DEFUN(AC_SS_FIND_QT_INCLUDE_DIR,
	[
		AC_ARG_WITH(qt-include-dir,[  --with-qt-include-dir   path to the Qt headers ],SS_QT_INCLUDE_DIR="$withval",SS_QT_INCLUDE_DIR="NOTGIVEN")
		if test "$SS_QT_INCLUDE_DIR" = "NOTGIVEN"; then

			AC_MSG_CHECKING(for Qt header files)

			ss_qt_include_test_dirs="/usr/include /usr/local/include /usr/qt/include /usr/local/qt/include /usr/X11R6/include /usr/lib/qt/include /usr/lib/qt /usr/include/X11"
			test -n "$QTDIR" && ss_qt_include_test_dirs="$QTDIR/include $QTDIR $ss_qt_include_test_dirs"
			ss_qt_include_test_dirs="$ss_qt_include_test_dirs /usr/include/qt /usr/local/include/qt /include/qt /usr/X11R6/include/qt /usr/build/qt/include"
			ss_qt_include_test_dirs="$ss_qt_include_test_dirs /usr/lib/qt3/include /usr/include/qt3 /usr/local/include/qt3 /include/qt3 /usr/X11R6/include/qt3 /usr/include/X11/qt3"
			test -n "$SS_QT_GENERAL_DIR" && ss_qt_include_test_dirs="$SS_QT_GENERAL_DIR/include $ss_qt_include_test_dirs"

			AC_SS_FIND_FILE_PATH(qiconview.h,$ss_qt_include_test_dirs,SS_QT_INCLUDE_DIR)

			if test "$SS_QT_INCLUDE_DIR" = "FAILED"; then
				AC_MSG_RESULT("FAILED")
				AC_SS_MESSAGE("CONFIGURE ERROR: cannot find qt headers")
				AC_MSG_ERROR(["This was a fatal one...aborting"])
			else
				AC_MSG_RESULT(found in $SS_QT_INCLUDE_DIR)
			fi

		else
			AC_MSG_RESULT(using user supplied path for the Qt include files $SS_QT_INCLUDE_DIR)
		fi
		CPPFLAGS="$CPPFLAGS -I$SS_QT_INCLUDE_DIR"
	]
)

AC_DEFUN(AC_SS_FIND_QT_LIBRARY_DIR,
	[
		AC_ARG_WITH(qt-library-dir,[  --with-qt-library-dir   path to the Qt library ],SS_QT_LIBRARY_DIR="$withval",SS_QT_LIBRARY_DIR="NOTGIVEN")
		if test "$SS_QT_LIBRARY_DIR" = "NOTGIVEN"; then
			AC_MSG_CHECKING(for the Qt library)

			ss_qt_library_test_dirs="$SS_QT_GENERAL_DIR/lib /lib /usr/lib /usr/local/lib /usr/qt/lib /usr/local/qt/lib /usr/X11R6/lib /usr/lib/qt/lib /usr/lib/qt /usr/local/lib/qt/lib"
			test -n "$QTDIR" && ss_qt_library_test_dirs="$QTDIR/lib $QTDIR $ss_qt_library_test_dirs"
			ss_qt_library_test_dirs="$ss_qt_library_test_dirs /usr/lib/qt3/lib /usr/local/lib/qt /usr/X11R6/lib/qt /usr/build/qt/lib"
			if test -n "$SS_QT_GENERAL_DIR"; then
				ss_qt_library_test_dirs="$SS_QT_GENERAL_DIR/lib $ss_qt_library_test_dirs"
			fi

			AC_SS_FIND_FILE_PATH(libqt-mt.so.3,$ss_qt_library_test_dirs,SS_QT_MT_LIBRARY_DIR)
			AC_SS_FIND_FILE_PATH(libqt.so.3,$ss_qt_library_test_dirs,SS_QT_LIBRARY_DIR)

			if test "$SS_QT_MT_LIBRARY_DIR" != "FAILED"; then
				AC_MSG_RESULT(found multithreaded version in $SS_QT_MT_LIBRARY_DIR)
				LIBS="$LIBS -L$SS_QT_MT_LIBRARY_DIR -lqt-mt"
			elif test "$SS_QT_LIBRARY_DIR" != "FAILED"; then
				AC_MSG_RESULT(found in $SS_QT_LIBRARY_DIR)
				LIBS="$LIBS -L$SS_QT_LIBRARY_DIR -lqt"
			else 
				AC_MSG_RESULT("FAILED")
				AC_SS_MESSAGE("CONFIGURE ERROR: cannot find qt library")
				AC_MSG_ERROR(["This was a fatal one...aborting"])
			fi
		else
			AC_MSG_RESULT(using user supplied path for the Qt multithread library $SS_QT_LIBRARY_DIR)
			LIBS="$LIBS -L$SS_QT_MT_LIBRARY_DIR -lqt-mt"
		fi
	]
)


AC_DEFUN(AC_SS_FIND_QT_MOC,
	[	
		AC_ARG_WITH(qt-moc,[  --with-qt-moc           filename of the Qt meta object compiler ],SS_QT_MOC="$withval",SS_QT_MOC="NOTGIVEN")
	 	if test "$SS_QT_MOC" = "NOTGIVEN"; then
	 		unset SS_QT_MOC
			if test -n "$SS_QT_GENERAL_DIR"; then
		 		AC_PATH_PROG(SS_QT_MOC,moc,"FAILED",$SS_QT_GENERAL_DIR/bin:$QTDIR/bin:$PATH:/usr/bin:/bin:/usr/local/bin:/usr/X11R6/bin:/usr/lib/qt/bin:/usr/local/qt/bin:/usr/X11R6/qt/bin:/usr/lib/qt3/bin:/usr/qt/bin:/usr/build/qt/bin)
			else
		 		AC_PATH_PROG(SS_QT_MOC,moc,"FAILED",$QTDIR/bin:$PATH:/usr/lib/qt3/bin:/usr/bin:/bin:/usr/local/bin:/usr/X11R6/bin:/usr/lib/qt/bin:/usr/local/qt/bin:/usr/X11R6/qt/bin:/usr/qt/bin:/usr/build/qt/bin)
			fi

			if test "$SS_QT_MOC" = "FAILED"; then
				AC_MSG_RESULT(["FAILED"])
				AC_SS_MESSAGE(["CONFIGURE ERROR: cannot find moc executable"])
				AC_MSG_ERROR(["This was a fatal one...aborting"])
			fi
		else
			AC_MSG_RESULT(using user supplied path for moc $SS_QT_MOC)
	 	fi
		MOC_PATH=$SS_QT_MOC
		AC_SUBST(MOC_PATH)
	]
)

AC_DEFUN(AC_SS_FIND_QT_UIC,
	[	
		AC_ARG_WITH(qt-uic,[  --with-qt-uic           filename of the Qt Interface compiler ],SS_QT_UIC="$withval",SS_QT_UIC="NOTGIVEN")
	 	if test "$SS_QT_UIC" = "NOTGIVEN"; then
	 		unset SS_QT_UIC
			if test -n "$SS_QT_GENERAL_DIR"; then
		 		AC_PATH_PROG(SS_QT_UIC,uic,"FAILED",$SS_QT_GENERAL_DIR/bin:$QTDIR/bin:$PATH:/usr/bin:/bin:/usr/local/bin:/usr/X11R6/bin:/usr/lib/qt/bin:/usr/local/qt/bin:/usr/X11R6/qt/bin:/usr/lib/qt3/bin:/usr/qt/bin:/usr/build/qt/bin)
			else
		 		AC_PATH_PROG(SS_QT_UIC,uic,"FAILED",$QTDIR/bin:$PATH:/usr/lib/qt3/bin:/usr/bin:/bin:/usr/local/bin:/usr/X11R6/bin:/usr/lib/qt/bin:/usr/local/qt/bin:/usr/X11R6/qt/bin:/usr/qt/bin:/usr/build/qt/bin)
			fi

			if test "$SS_QT_UIC" = "FAILED"; then
				AC_MSG_RESULT(["FAILED"])
				AC_SS_MESSAGE(["CONFIGURE ERROR: cannot find uic executable"])
				AC_MSG_ERROR(["This was a fatal one...aborting"])
			fi
		else
			AC_MSG_RESULT(using user supplied path for uic $SS_QT_UIC)
	 	fi
		UIC_PATH=$SS_QT_UIC
		AC_SUBST(UIC_PATH)
	]
)
