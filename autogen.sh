MACRO_FILES="macro/generic.m4 macro/qt.m4 macro/qwt.m4 macro/kde.m4 macro/blas.m4 macro/lapack.m4"

cat $MACRO_FILES > acinclude.m4
aclocal 
autoheader
automake --add-missing
autoconf 
