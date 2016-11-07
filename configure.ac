AC_INIT([wxMoldeoControls], [0.9.2], [info@moldeointeractive.com.ar], [wxMoldeoControls])

AM_INIT_AUTOMAKE

#INTI_REQUIRED_VERSION=1.0.7
#PKG_CHECK_MODULES(INTI, inti-1.0 >= $INTI_REQUIRED_VERSION)
#AC_SUBST(INTI_CFLAGS)
#AC_SUBST(INTI_LIBS)

AC_PROG_CXX
AC_PROG_CC
AC_C_CONST
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL

AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_CXX_C_O


# Checks for libraries.
dnl Check gtk+-2.0
PKG_CHECK_MODULES([GTK2], [gtk+-2.0] ,has_gtk2=yes)

dnl Check wx-Widgets
WX_CONFIG_CHECK([2.8.0], [wxWin=1], [wxWin=0], [html,core,net,gl,aui], [--unicode])

WX_GTK2_CFLAGS=
WX_GTK2_LIBS=

dnl default value is to (silently) do nothing in the makefile
POSTLINK_COMMAND="@true"
MACSETFILE="@true"

AC_MSG_CHECKING(for wxWidgets platform)
WX_BASENAME=`$WX_CONFIG_WITH_ARGS --basename`
case $WX_BASENAME in 
    *wx_gtk*)
        AC_MSG_RESULT(wxGTK)
        WX_GTK2_CFLAGS="$GTK2_CFLAGS"
        WX_GTK2_LIBS="$GTK2_LIBS"
    ;;
    *wx_msw*)
        AC_MSG_RESULT(wxMSW)
    ;;
    *wx_mac*)
        AC_MSG_RESULT(wxMac)
        AC_CHECK_PROG(REZ, Rez, Rez, /Developer/Tools/Rez)
        POSTLINK_COMMAND="\$(REZ) -d __DARWIN__ -t APPL Carbon.r -o"
        AC_CHECK_PROG(SETFILE, SetFile, SetFile, /Developer/Tools/SetFile)
        MACSETFILE="\$(SETFILE)"
    ;;
    *) 
        AC_MSG_RESULT(other)
    ;;
esac

LIBWXMOLDEOCONTROLS_CFLAGS=-I../wxMoldeoControls
LIBWXMOLDEOCONTROLS_LIBS=-lmoldeocontrols
LIBWXMOLDEOCONTROLS_LDFLAGS=-L../wxMoldeoControls/.libs
AC_SUBST(LIBWXMOLDEOCONTROLS_CFLAGS)
AC_SUBST(LIBWXMOLDEOCONTROLS_LDFLAGS)
AC_SUBST(LIBWXMOLDEOCONTROLS_LIBS)

AC_SUBST(WX_GTK2_CFLAGS)
AC_SUBST(WX_GTK2_LIBS)

AC_SUBST(POSTLINK_COMMAND)
AC_SUBST(MACSETFILE)

PLUGIN_WX_LIBS=

AC_MSG_CHECKING(if wxWidgets libraries are needed for plugins)
case `uname` in 
    Darwin)
        AC_MSG_RESULT(yes)
        PLUGIN_WX_LIBS="$WX_LIBS"
    ;;
    *) 
        AC_MSG_RESULT(no)
    ;;
esac

AC_SUBST(PLUGIN_WX_LIBS)

dnl Additional arguments (and substitutions)
dnl Allow the pkg-config directory to be set
AC_ARG_WITH(pkgconfigdir,
	AC_HELP_STRING([--with-pkgconfigdir],
	[Use the specified pkgconfig dir (default is libdir/pkgconfig)]),
	[pkgconfigdir=${withval}],
	[pkgconfigdir='${libdir}/pkgconfig'])

AC_SUBST([pkgconfigdir])


dnl autoscan results
AC_CHECK_FUNCS([floor])
AC_CHECK_FUNCS([getcwd])
AC_CHECK_FUNCS([memmove])
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([rint])
AC_CHECK_FUNCS([sqrt])
AC_CHECK_FUNCS([strchr])
AC_CHECK_FUNCS([strstr])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([float.h])
AC_CHECK_HEADERS([limits.h])
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_TYPES([ptrdiff_t])
AC_C_INLINE
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_VPRINTF
AC_HEADER_STDBOOL
AC_HEADER_STDC
AC_PREREQ
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
LT_INIT
AC_STRUCT_TM
AC_TYPE_SIZE_T

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_OUTPUT(Makefile wxMoldeoControls/Makefile wxMoldeoControlsTest/Makefile moldeocontrols.pc )
