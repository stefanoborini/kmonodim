#### general
####

AC_DEFUN(AC_SS_MESSAGE,
[
	echo $1
])

AC_DEFUN(AC_SS_CXXFLAGS,
[
	AC_MSG_CHECKING([If you want the debug symbols...])
	AC_ARG_WITH(debug-symbols, [  --with-debug-symbols    Specifies to leave the debug symbols in the executable],SS_ADD_DEBUG_SYMBOLS="true")

	CXXFLAGS=""

	if test -n "$SS_ADD_DEBUG_SYMBOLS"; then
		AC_MSG_RESULT([yes])
		CXXFLAGS="-g"
	else
		AC_MSG_RESULT([no])
	fi

	AC_MSG_CHECKING([If you want O3 optimisation...])
	AC_ARG_WITH(o3-optimisation, [  --with-o3-optimisation  Specifies to use the O3 flag when compiling],SS_O3_OPTIMISATION="true")

	if test -n "$SS_O3_OPTIMISATION"; then
		AC_MSG_RESULT([yes])
		CXXFLAGS="$CXXFLAGS -O3"
	else
		AC_MSG_RESULT([no])
		CXXFLAGS="$CXXFLAGS -O2"
	fi

])

AC_DEFUN(AC_SS_FIND_FILE_PATH,
	[
		$3="FAILED"
		for a_dir in $2; do
			for a_file in $1; do
				if test -r "$a_dir/$a_file"; then
					$3=$a_dir
					break 2
				fi
			done
		done	
	]
)

AC_DEFUN(AC_SS_FIND_FILE_PATH_EXT,
	[
		$4="FAILED"

		for a_dir in $2; do
			for a_semidir in $3; do
				for a_file in $1; do
					if test -r "$a_dir/$a_semidir/$a_file"; then
						$4="$a_dir/$a_semidir"
						break 3
					fi
				done
			done
		done
	]
)

#### search qt
#### 

AC_DEFUN(AC_SS_FIND_QT_INCLUDE_DIR,
	[
		AC_ARG_WITH(qt-include-dir,[  --with-qt-include-dir   path to the Qt headers ],SS_QT_INCLUDE_DIR="$withval",SS_QT_INCLUDE_DIR="NOTGIVEN")
		if test "$SS_QT_INCLUDE_DIR" = "NOTGIVEN"; then

			AC_MSG_CHECKING(for Qt header files)

			ss_qt_include_test_dirs="$SS_QT_GENERAL_DIR/include /include /usr/include /usr/local/include /usr/qt/include /usr/local/qt/include /usr/X11R6/include /usr/lib/qt/include /usr/lib/qt /usr/include/X11"
			test -n "$QTDIR" && ss_qt_include_test_dirs="$QTDIR/include $QTDIR $ss_qt_include_test_dirs"
			ss_qt_include_test_dirs="$ss_qt_include_test_dirs /usr/include/qt /usr/local/include/qt /include/qt /usr/X11R6/include/qt /usr/build/qt/include"
			ss_qt_include_test_dirs="$ss_qt_include_test_dirs /usr/include/qt2 /usr/local/include/qt2 /include/qt2 /usr/X11R6/include/qt2 /usr/include/X11/qt2"
			test -n "$SS_QT_GENERAL_DIR" && ss_qt_include_test_dirs="$SS_QT_GENERAL_DIR/include $ss_qt_include_test_dirs"

			AC_SS_FIND_FILE_PATH(qiconview.h,$ss_qt_include_test_dirs,SS_QT_INCLUDE_DIR)

			if test "$SS_QT_INCLUDE_DIR" = "FAILED"; then
				AC_MSG_RESULT("FAILED")
				AC_SS_MESSAGE("CONFIGURE ERROR: cannot find qt headers");
				AC_MSG_ERROR(["This was a fatal one...aborting"])
			else
				AC_MSG_RESULT(found in $SS_QT_INCLUDE_DIR)
			fi

		else
			AC_MSG_RESULT(using user supplied path for the Qt include files $SS_QT_INCLUDE_DIR)
		fi
		CPPFLAGS="$CPPFLAGS $SS_QT_INCLUDE_DIR"
	]
)

AC_DEFUN(AC_SS_FIND_QT_LIBRARY_DIR,
	[
		AC_ARG_WITH(qt-library-dir,[  --with-qt-library-dir   path to the Qt library ],SS_QT_LIBRARY_DIR="$withval",SS_QT_LIBRARY_DIR="NOTGIVEN")
		if test "$SS_QT_LIBRARY_DIR" = "NOTGIVEN"; then
			AC_MSG_CHECKING(for the Qt library)

			ss_qt_library_test_dirs="$SS_QT_GENERAL_DIR/lib /lib /usr/lib /usr/local/lib /usr/qt/lib /usr/local/qt/lib /usr/X11R6/lib /usr/lib/qt/lib /usr/lib/qt /usr/local/lib/qt/lib"
			test -n "$QTDIR" && ss_qt_library_test_dirs="$QTDIR/lib $QTDIR $ss_qt_library_test_dirs"
			ss_qt_library_test_dirs="$ss_qt_library_test_dirs /usr/local/lib/qt /usr/X11R6/lib/qt /usr/build/qt/lib"
			if test -n "$SS_QT_GENERAL_DIR"; then
				ss_qt_library_test_dirs="$SS_QT_GENERAL_DIR/lib $ss_qt_library_test_dirs"
			fi

			AC_SS_FIND_FILE_PATH(libqt.so.2,$ss_qt_library_test_dirs,SS_QT_LIBRARY_DIR)

			if test "$SS_QT_LIBRARY_DIR" = "FAILED"; then
				AC_MSG_RESULT("FAILED")
				AC_SS_MESSAGE("CONFIGURE ERROR: cannot find qt library")
				AC_MSG_ERROR(["This was a fatal one...aborting"])
			else
				AC_MSG_RESULT(found in $SS_QT_LIBRARY_DIR)
			fi
		else
			AC_MSG_RESULT(using user supplied path for the Qt library $SS_QT_LIBRARY_DIR)
		fi
		LIBS="$LIBS $SS_QT_LIBRARY_DIR"
	]
)


AC_DEFUN(AC_SS_FIND_QT_MOC,
	[	
		AC_ARG_WITH(qt-moc,[  --with-qt-moc           filename of the Qt meta object compiler ],SS_QT_MOC="$withval",SS_QT_MOC="NOTGIVEN")
	 	if test "$SS_QT_MOC" = "NOTGIVEN"; then
	 		unset SS_QT_MOC
			if test -n "$SS_QT_GENERAL_DIR"; then
		 		AC_PATH_PROG(SS_QT_MOC,moc,"FAILED",$SS_QT_GENERAL_DIR/bin:$QTDIR/bin:$PATH:/usr/bin:/bin:/usr/local/bin:/usr/X11R6/bin:/usr/lib/qt/bin:/usr/local/qt/bin:/usr/X11R6/qt/bin:/usr/qt/bin:/usr/build/qt/bin)
			else
		 		AC_PATH_PROG(SS_QT_MOC,moc,"FAILED",$QTDIR/bin:$PATH:/usr/bin:/bin:/usr/local/bin:/usr/X11R6/bin:/usr/lib/qt/bin:/usr/local/qt/bin:/usr/X11R6/qt/bin:/usr/qt/bin:/usr/build/qt/bin)
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

AC_DEFUN(AC_SS_FIND_QWT_LIBRARY_DIR,
[
	AC_ARG_WITH(qwt-library-dir,[  --with-qwt-library-dir      Path to the Qwt Widget set library",SS_QWT_LIBRARY_DIR="$withval",SS_QWT_LIBRARY_DIR="NOTGIVEN")
	if test "$SS_QWT_LIBRARY_DIR" = "NOTGIVEN"; then
		unset SS_QWT_LIBRARY_DIR

		AC_MSG_CHECKING(for the Qwt widget library)
		ss_qwt_library_test_dirs="/lib /usr/lib /usr/local/lib /usr/qwt/lib /usr/local/qwt/lib /usr/X11R6/lib /usr/lib/qwt/lib /usr/lib/qwt /usr/local/lib/qwt/lib"

		AC_SS_FIND_FILE_PATH(libqwt.so.0.3,$ss_qwt_library_test_dirs,SS_QWT_LIBRARY_DIR)

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
	LIBS="$LIBS $SS_QWT_LIBRARY_DIR"
])

AC_DEFUN(AC_SS_FIND_QWT_INCLUDE_DIR,
[
	AC_ARG_WITH(qwt-include-dir,[  --with-qwt-include-dir      Path to the Qwt Widget set include files",SS_QWT_INCLUDE_DIR="$withval",SS_QWT_INCLUDE_DIR="NOTGIVEN")
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
	CPPFLAGS="$CPPFLAGS $SS_QWT_INCLUDE_DIR"
])
