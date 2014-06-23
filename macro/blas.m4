
AC_DEFUN(AC_SS_FIND_BLAS_LIBRARY_DIR,
[
	AC_ARG_WITH(blas-library-dir,[  --with-blas-library-dir      Path to the blas library],SS_BLAS_LIBRARY_DIR="$withval",SS_BLAS_LIBRARY_DIR="NOTGIVEN")
	if test "$SS_BLAS_LIBRARY_DIR" = "NOTGIVEN"; then
		unset SS_BLAS_LIBRARY_DIR

		AC_MSG_CHECKING(for the BLAS widget library)
		ss_blas_library_test_dirs="/lib /usr/lib /usr/local/lib"

		AC_SS_FIND_FILE_PATH(libblas.so,$ss_blas_library_test_dirs,SS_BLAS_LIBRARY_DIR)

		if test "$SS_BLAS_LIBRARY_DIR" = "FAILED"; then
			AC_MSG_RESULT("FAILED")
			AC_SS_MESSAGE("CONFIGURE ERROR: cannot find blas library")
			AC_MSG_ERROR(["This was a fatal one...aborting"])
		else
			AC_MSG_RESULT(found in $SS_BLAS_LIBRARY_DIR)
		fi
	else
		AC_MSG_RESULT(using user supplied path for the blas Library $SS_BLAS_LIBRARY_DIR)
	fi
	LIBS="$LIBS -L$SS_BLAS_LIBRARY_DIR -lblas -lg2c"
])

