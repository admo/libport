# URBI_WITH_ORBIX
# ----------
# Look for ORBIX.  Support --with-ORBIX=PATH. Check the software
# location.
#
# Output variable ORBIX_PATH point to the installation location.
# Set "$ORBIX" to "true" or "false".
AC_DEFUN([URBI_WITH_ORBIX],
[AC_ARG_WITH([ORBIX],
	     [AC_HELP_STRING([--with-ORBIX=ORBIX-path],
			     [enable ORBIX support [/usr/local/IONA/OBE/2.2n]])],
	     [], [with_ORBIX=yes])

case $with_ORBIX in
   no) ORBIX=false
       ;;
  yes) ORBIX=true
       ORBIX_PATH=/usr/local/IONA/OBE/2.2n
       ;;
    *) ORBIX=true
       ORBIX_PATH=$with_ORBIX
       ;;
esac

# Checking whether ORBIX is really there.
AC_MSG_CHECKING([for ORBIX])
if $ORBIX; then
  if (test -d "$ORBIX_PATH"); then
    AC_MSG_RESULT([$ORBIX_PATH])
    ORBIX=true
  else
    AC_MSG_RESULT([no, ORBIX not found in $ORBIX_PATH])
    ORBIX=false
  fi
else
  AC_MSG_RESULT([no])
  ORBIX=false
fi

if $ORBIX; then
  # More tools for ORBIX.
  AC_SUBST([ORBIX_PATH], ['$(ORBIX_PATH)'])
  AC_SUBST([ORBIX_INCLUDE],
    ['-I$(top_srcdir)/$(ORBIX_PATH)/acpp/include
      -I$(top_srcdir)/$(ORBIX_PATH)/c/include'])
  AC_SUBST([ORBIX_ORB], ['ORBIXE'])
  AC_SUBST([ORBIX_VERSION], ['2'])

  AC_SUBST([ORBIX_CPPFLAGS],
    ['$(ORBIX_INCLUDE) -D$(ORBIX_ORB) -DVERSION=$(ORBIX_VERSION)'])
fi

AM_CONDITIONAL([WITH_ORBIX], [$ORBIX])
AC_SUBST([ORBIX_PATH])
])

AC_DEFUN([URBI_WITH_ORBIX_REQUIRED],
[
   AC_REQUIRE([URBI_WITH_ORBIX])

   case $ORBIX in
     '' | false)
       AC_MSG_ERROR([Failed to find ORBIX. Please install it or check config.log])
     ;;
   esac
])


## Local Variables:
## mode: autoconf
## End:
