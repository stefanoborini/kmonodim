%define name kmonodim
%define version 2.0.1
%define release 1
%define prefix %{_prefix}

Summary: Simple monodimensional solver
Name: %{name}
Version: %{version}
Release: %{release}
Copyright: GPL
Group: Sciences/Chemistry
URL: http://icbe61.unife.it/kmonodim
Source: kmonodim-2.0.1.tar.gz
Distribution: Linux-RedHat
Vendor: RedHat
Packager: Stefano Borini <stef@chim251.unife.it>
Requires: libqt3 qwt >= 0.4.1 blas lapack
Buildroot: %{_tmppath}/%{name}-build/
Obsoletes: %{name}
Provides:  %{name}
%description
KMonodim is a simple solver for monodimensional problems. It current solves
problems with various potentials such as square well, square well with a
barrier, parabolic and morse potential. It provides calculation of eigenvalues
and eigenfunctions for a given system, richardson extrapolation to achieve
better precision, load and save in XML format, simultaneous work on multiple
system, integral evaluation.

%prep 
%setup -q -n %{name}-%{version}
%build
./autogen.sh
%configure 
make

%install
%makeinstall

%files
%defattr(-,root,root)
%attr(755,root,root) %{_bindir}/kmonodim

%clean
rm -rf $RPM_BUILD_ROOT

%changelog
* Tue Aug 12 2003 Stefano Borini <stef@chim251.unife.it>
- release 2.0.1 merges Michael Torrie patches in the official CVS.
  Provided fixes for m4 macros to be more comfortable with different
  environments (I hope so)
* Tue Jul 22 2003 Michael Torrie <torriem@byu.edu>
- Ported kmonodim to kde3/qt3
- patched m4 macros to detect kde3/qt3
* Tue Jan 07 2003 Stefano Borini <stef@chim251.unife.it>
- Updated to kmonodim 2.0 beta
* Tue Nov 19 2001 Stefano Borini <stef@chim251.unife.it> 
- First RPM release
