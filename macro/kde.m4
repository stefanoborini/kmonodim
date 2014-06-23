#### search kde
#### 


AC_DEFUN(AC_SS_FIND_KDE_INCLUDE_DIR,
	[
		AC_ARG_WITH(kde-include-dir,[  --with-kde-include-dir   path to the kde headers ],SS_KDE_INCLUDE_DIR="$withval",SS_KDE_INCLUDE_DIR="NOTGIVEN")
		if test "$SS_KDE_INCLUDE_DIR" = "NOTGIVEN"; then

			AC_MSG_CHECKING(for kde header files)

			ss_kde_include_test_dirs="/usr/include /usr/local/include /usr/kde/include /usr/local/kde/include /usr/X11R6/include /usr/lib/kde/include /usr/lib/kde /usr/include/X11 /opt/kde/include"
			test -n "$KDEDIR" && ss_kde_include_test_dirs="$KDEDIR/include $KDEDIR $ss_kde_include_test_dirs"
			ss_kde_include_test_dirs="$ss_kde_include_test_dirs /usr/include/kde /usr/local/include/kde /include/kde /usr/X11R6/include/kde /usr/build/kde/include"
			ss_kde_include_test_dirs="$ss_kde_include_test_dirs /usr/include/kde2 /usr/local/include/kde2 /include/kde2 /usr/X11R6/include/kde2 /usr/include/X11/kde2"
			test -n "$SS_KDE_GENERAL_DIR" && ss_kde_include_test_dirs="$SS_KDE_GENERAL_DIR/include $ss_kde_include_test_dirs"

			AC_SS_FIND_FILE_PATH(kmainwindow.h,$ss_kde_include_test_dirs,SS_KDE_INCLUDE_DIR)

			if test "$SS_KDE_INCLUDE_DIR" = "FAILED"; then
				AC_MSG_RESULT("FAILED")
				AC_SS_MESSAGE("CONFIGURE ERROR: cannot find kde headers")
				AC_MSG_ERROR(["This was a fatal one...aborting"])
			else
				AC_MSG_RESULT(found in $SS_KDE_INCLUDE_DIR)
			fi

		else
			AC_MSG_RESULT(using user supplied path for the kde include files $SS_KDE_INCLUDE_DIR)
		fi
		CPPFLAGS="$CPPFLAGS -I$SS_KDE_INCLUDE_DIR"
	]
)

AC_DEFUN(AC_SS_FIND_KDE_LIBRARY_DIR,
	[
		AC_ARG_WITH(kde-library-dir,[  --with-kde-library-dir   path to the kde library ],SS_KDE_LIBRARY_DIR="$withval",SS_KDE_LIBRARY_DIR="NOTGIVEN")
		if test "$SS_KDE_LIBRARY_DIR" = "NOTGIVEN"; then
			AC_MSG_CHECKING(for the kde library)

			ss_kde_library_test_dirs="$SS_KDE_GENERAL_DIR/lib /lib /usr/lib /usr/local/lib /usr/kde/lib /usr/local/kde/lib /usr/X11R6/lib /usr/lib/kde/lib /usr/lib/kde /usr/local/lib/kde/lib /opt/kde/lib"
			test -n "$KDEDIR" && ss_kde_library_test_dirs="$KDEDIR/lib $KDEDIR $ss_kde_library_test_dirs"
			ss_kde_library_test_dirs="$ss_kde_library_test_dirs /usr/local/lib/kde /usr/X11R6/lib/kde /usr/build/kde/lib"
			if test -n "$SS_KDE_GENERAL_DIR"; then
				ss_kde_library_test_dirs="$SS_KDE_GENERAL_DIR/lib $ss_kde_library_test_dirs"
			fi

			AC_SS_FIND_FILE_PATH(libkdecore.so.4,$ss_kde_library_test_dirs,SS_KDE3_LIBRARY_DIR)
			AC_SS_FIND_FILE_PATH(libkdecore.so.3,$ss_kde_library_test_dirs,SS_KDE2_LIBRARY_DIR)

			if test "$SS_KDE3_LIBRARY_DIR" != "FAILED"; then
				AC_MSG_RESULT(found libkdecore.so.4 in $SS_KDE3_LIBRARY_DIR)
				LIBS="$LIBS -L$SS_KDE3_LIBRARY_DIR -lkdecore -lkdeui -lkio"
			elif test "$SS_KDE2_LIBRARY_DIR" != "FAILED"; then
				AC_MSG_RESULT(found libkdecore.so.3 in $SS_KDE2_LIBRARY_DIR)
				LIBS="$LIBS -L$SS_KDE2_LIBRARY_DIR -lkdecore -lkdeui -lkfile"
			else 
				AC_MSG_RESULT("FAILED")
				AC_SS_MESSAGE("CONFIGURE ERROR: cannot find kde library")
				AC_MSG_ERROR(["This was a fatal one...aborting"])
			fi
		else
			AC_MSG_RESULT(using user supplied path for the kde3 library $SS_KDE_LIBRARY_DIR)
			LIBS="$LIBS -L$SS_KDE_LIBRARY_DIR -lkdecore -lkdeui -lkio"
		fi
	]
)

