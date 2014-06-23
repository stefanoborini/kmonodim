AC_DEFUN(AC_SS_FIND_LAPACK_LIBRARY_DIR,
[
	AC_ARG_WITH(lapack-library-dir,[  --with-lapack-library-dir      Path to the Lapack library],SS_LAPACK_LIBRARY_DIR="$withval",SS_LAPACK_LIBRARY_DIR="NOTGIVEN")
	if test "$SS_LAPACK_LIBRARY_DIR" = "NOTGIVEN"; then
		unset SS_LAPACK_LIBRARY_DIR

		AC_MSG_CHECKING(for the Lapack widget library)
		ss_lapack_library_test_dirs="/lib /usr/lib /usr/local/lib"

		AC_SS_FIND_FILE_PATH(liblapack.so,$ss_lapack_library_test_dirs,SS_LAPACK_LIBRARY_DIR)

		if test "$SS_LAPACK_LIBRARY_DIR" = "FAILED"; then
			AC_MSG_RESULT("FAILED")
			AC_SS_MESSAGE("CONFIGURE ERROR: cannot find Lapack library")
			AC_MSG_ERROR(["This was a fatal one...aborting"])
		else
			AC_MSG_RESULT(found in $SS_LAPACK_LIBRARY_DIR)
		fi
	else
		AC_MSG_RESULT(using user supplied path for the Lapack Library $SS_LAPACK_LIBRARY_DIR)
	fi
	LIBS="$LIBS -L$SS_LAPACK_LIBRARY_DIR -llapack"
])

