m4_pattern_forbid([^URBI_])dnl

AC_PREREQ([2.60])

# _URBI_DIRS(KIND, DEFAULT-URBI-ENV)
# ----------------------------------
# KIND should be "core" or "kernel".
# DEFAULT-URBI-ENV should probably be something like "aibo", "webots" etc.
#
# Define the directory variables we are about to use:
#
# branddir	   = $(prefix)/$(PACKAGE_BRAND)
#                    /usr/local/gostai
# hostdir	   = $(branddir)/KIND/$(URBI_HOST)
# envdir	   = $(hostdir)/$(URBI_ENV)
#                    /usr/local/gostai/core/aibo
# kerneldir	   = $(branddir)/kernel/$(URBI_HOST)/$(URBI_ENV)
#                    /usr/local/gostai/kernel/aibo
# sdkincludedir	   = $(branddir)/KIND/include
# kernelincludedir = $(branddir)/kernel/include
m4_define([_URBI_DIRS],
[m4_bmatch([$1],
	   [core\|kernel], [],
	   [m4_fatal([incorrect kind: $1])])

# We need to know the host (the type of architecture it will run on),
# the environment (the runtime, the event loop: posix, webots, aibo).

# URBI_HOST
AC_ARG_ENABLE([host],
	      [AC_HELP_STRING([--enable-host=urbi-host],
			      [The machine this will run on [HOST]])])
AC_REQUIRE([AC_CANONICAL_HOST])
AC_MSG_CHECKING([for URBI host type])
case $enable_host:$host_alias in
  '':'') URBI_HOST=$host;;
  '':* ) URBI_HOST=$host_alias;;
   *:* ) URBI_HOST=$enable_host;;
esac
AC_MSG_RESULT([$URBI_HOST])
AC_SUBST([URBI_HOST])

# URBI_ENV
AC_ARG_ENABLE([env],
	      [AC_HELP_STRING([--enable-env=urbi-env],
			      [The environment this will run on:
			       aibo, webots, posix [posix]])])
AC_MSG_CHECKING([for URBI environment type])
case $enable_env in
 '') URBI_ENV=$2;;
  *) URBI_ENV=$enable_env;;
esac
AC_MSG_RESULT([$URBI_ENV])
case $URBI_ENV in
  aibo)
     AC_DEFINE([URBI_ENV_AIBO], [1], [Define if compiling for Aibo.])
     ;;
  posix)
     AC_DEFINE([URBI_ENV_POSIX], [1], [Define if compiling for POSIX.])
     ;;
  webots)
     AC_DEFINE([URBI_ENV_WEBOTS], [1], [Define if compiling for Webots.])
     ;;
  *)
     AC_MSG_NOTICE([[unknow environment type: $URBI_ENV]])
     ;;
esac
AC_SUBST([URBI_ENV])

# Everything is installed in $prefix/gostai.
AC_SUBST([PACKAGE_BRAND], [gostai])
AC_SUBST([branddir], ['$(prefix)/$(PACKAGE_BRAND)'])

# Standard headers and libraries are installed in regular
# includedir and libdir under $prefix.

# /usr/local/gostai/core/$host
AC_SUBST([hostdir], ['$(branddir)/$1/$(URBI_HOST)'])

# /usr/local/gostai/core/$host/$env.
# Could have been named sdklibdir too.
AC_SUBST([envdir], ['$(hostdir)/$(URBI_ENV)'])
# Possibly an alias: /usr/local/gostai/kernel/powerpc-apple-darwin8.7.0/posix
AC_SUBST([kerneldir],  ['$(branddir)/kernel/$(URBI_HOST)/$(URBI_ENV)'])

# Where we install, and expect to find, headers.
AC_SUBST([sdkincludedir],  ['$(branddir)/$1/include'])
# Possibly an alias.
AC_SUBST([kernelincludedir],  ['$(branddir)/kernel/include'])

# In the case we are compiling the kernel, we do not want to add
# these, otherwise we might try to build a kernel using installed
# files, instead of its own shipped files.
if test "$1" != kernel; then
  CPPFLAGS="$CPPFLAGS -I$sdkincludedir"
  LDFLAGS="$LDFLAGS -L$envdir"
fi
])

# To be used by liburbi and sdks.
AC_DEFUN([URBI_DIRS],         [_URBI_DIRS([core],   [$1])])
# To be used by core developpers for the kernels.
AC_DEFUN([URBI_KERNEL_DIRS],  [_URBI_DIRS([kernel], [$1])])



## Local Variables:
## mode: autoconf
## End:
