#global commit 998c69898058a7917a35875b7c7591bba6cf9f48
#global shortcommit %(c=%{commit}; echo ${c:0:7})

Name:           qbs
# qbs was previously packaged as part of qt-creator, using the qt-creator version, hence the epoch bump
Epoch:          1
Version:        1.10
Release:        1
Summary:        Cross platform build tool

# See LGPL_EXCEPTION.txt
License:        LGPLv2 with exceptions and LGPLv3 with exceptions
URL:            https://wiki.qt.io/qbs
Source0:        %{name}-%{version}.tar.gz

# Don't add /usr/include to INCLUDEPATH in qbs pri, it can result in
# isystem /usr/include being added projects including use_installed_corelib.pri
#Patch0:         qbs_includepath.patch

BuildRequires:  qt5-qtcore-devel
BuildRequires:  qt5-qtnetwork-devel
BuildRequires:  qt5-qttest-devel
BuildRequires:  qt5-qtxml-devel
BuildRequires:  qt5-qttools-qdoc
BuildRequires:  qt5-qtscript-devel
BuildRequires:  qt5-qtconcurrent-devel
BuildRequires:  mer-qdoc-template


%description
Qbs is a tool that helps simplify the build process for developing projects
across multiple platforms. Qbs can be used for any software project, regardless
of programming language, toolkit, or libraries used.

Qbs is an all-in-one tool that generates a build graph from a high-level
project description (like qmake or CMake) and additionally undertakes the task
of executing the commands in the low-level build graph (like make).


%package        devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{epoch}:%{version}-%{release}


%description devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.


%package        examples
Summary:        Example projects using %{name}
Requires:       %{name} = %{epoch}:%{version}-%{release}
BuildArch:      noarch

%description    examples
The %{name}-examples package contains example files for using %{name}.

%prep
%setup -q -n %{name}-%{version}

%build
%qmake5 \
  QBS_INSTALL_PREFIX="/usr" \
  CONFIG+=qbs_enable_project_file_updates \
  CONFIG+=qbs_disable_rpath \
  CONFIG+=qbs_enable_unit_tests \
  CONFIG+=nostrip \
  QMAKE_LFLAGS="-Wl,--as-needed" \
  qbs.pro
make

%install
make install INSTALL_ROOT=%{buildroot}

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig


%files
%doc README
%{_bindir}/%{name}*
%{_libdir}/%{name}/
%{_libdir}/libqbs*.so.1
%{_libdir}/libqbs*.so.1.10
%{_libdir}/libqbs*.so.1.10.*
%{_datadir}/%{name}/
%{_libexecdir}/%{name}
%exclude %{_datadir}/%{name}/examples

%files devel
%{_includedir}/%{name}/
%{_libdir}/libqbs*.so
%{_libdir}/libqbs*.prl
%{_mandir}/man1/

%files examples
%{_datadir}/%{name}/examples/
