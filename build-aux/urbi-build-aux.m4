dnl
# urbi-build-aux.m4: This file is part of build-aux.
# Copyright (C) Gostai S.A.S., 2006-2008.
dnl
# This software is provided "as is" without warranty of any kind,
# either expressed or implied, including but not limited to the
# implied warranties of fitness for a particular purpose.
dnl
# See the LICENSE file for more information.
# For comments, bug reports and feedback: http://www.urbiforge.com
dnl

m4_pattern_forbid([^URBI_])dnl

AC_PREREQ([2.60])

# URBI_BUILD_AUX
# --------------
# Initialize various things for build-aux/.
AC_DEFUN([URBI_BUILD_AUX],
[# Auxiliary files.
# Currently, because libtoolize does not support traces, don't move the
# AC_CONFIG_AUX_DIR here.
# AC_CONFIG_AUX_DIR([build-aux])

# Use install-sh -C for headers.
AC_SUBST([install_sh_c_DATA], ['$(install_sh)-c -c -m 644'])
AC_SUBST([INSTALL_HEADER], ['$(install_sh_c_DATA) -C'])

# Default value.
AC_SUBST([SVN], [svn])
])


## Local Variables:
## mode: autoconf
## End:
