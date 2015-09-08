Name: eio
Summary: Enlightenment Input/Output Library
Version: 1.7.1+svn.77392+build04
Release: 1
License: LGPL-2.1+
Group: System Environment/Libraries
URL: http://www.enlightenment.org/
Source0:    %{name}-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  eet-tools
BuildRequires:  eina-devel
BuildRequires:  eet-devel
BuildRequires:  ecore-devel


%description
Enlightenment input/output library


%package devel
Summary: EIO headers, static libraries, documentation and test programs
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}


%description devel
Headers, static libraries, test programs and documentation for EIO


%prep
%setup -q


%build
export CFLAGS+=" -fvisibility=hidden -fPIC -Wall"
export LDFLAGS+=" -fvisibility=hidden -Wl,--hash-style=both -Wl,--as-needed"

%autogen

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/usr/share/license
cp %{_builddir}/%{buildsubdir}/COPYING %{buildroot}/usr/share/license/%{name}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)
/usr/lib/*.so.*
%manifest %{name}.manifest
/usr/share/license/%{name}

%files devel
%defattr(-, root, root)
/usr/include/*
/usr/lib/libeio.so
/usr/lib/pkgconfig/eio.pc
