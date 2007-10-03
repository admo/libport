m4_pattern_forbid([^URBI_])dnl

AC_PREREQ([2.60])

# URBI_DOC
# --------
AC_DEFUN([URBI_DOC],
[
## --------------- ##
## Documentation.  ##
## --------------- ##

URBI_ARG_PROGS([doxygen], [the Doxygen documentation generation program])
# Name of the directory where the Doxygen documentation is created.
AC_SUBST([DOCDIR], [srcdoc])

AC_CONFIG_FILES([doc/Makefile
		 doc/Doxyfile:build-aux/Doxyfile.in])

ENABLE_DOC
])

AC_DEFUN([ENABLE_DOC],
[AC_ARG_ENABLE([doc],
   AS_HELP_STRING([--enable-doc],
                  [Turn on documentation (default is NO)]),
     [case "${enableval}" in
       yes|true|"") doc_output=doc; doc_install=doc-install; doc_uninstall=doc-uninstall;;
       no|false)  doc_output=; doc_install=; doc_uninstall=;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-doc]) ;;
     esac],
  [doc_output=; doc_install=; doc_uninstall=])
#AM_CONDITIONAL([COND_DOC_OUTPUT], [test x$doc_output = xtrue])
AC_SUBST([COND_DOC_OUTPUT], [$doc_output])
AC_SUBST([COND_DOC_INSTALL], [$doc_install])
AC_SUBST([COND_DOC_UNINSTALL], [$doc_uninstall])
])

## Local Variables:
## mode: autoconf
## End:
