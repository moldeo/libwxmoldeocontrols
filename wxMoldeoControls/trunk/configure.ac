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

AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_CXX_C_O


# Checks for libraries.
dnl Check gtk+-2.0
PKG_CHECK_MODULES([GTK2], [gtk+-2.0] ,has_gtk2=yes)

dnl Check wx-Widgets
AC_ARG_ENABLE([unicode],[AC_HELP_STRING([--disable-unicode],[internally use ansi])], 
	[AS_IF([test "x$enableval" = "xno"],[wx_config_args="--unicode=no"])
	AS_IF([test "x$enableval" = "xyes"],[wx_config_args="--unicode=yes"])],
	[wx_config_args="--unicode=no"])
AM_OPTIONS_WXCONFIG
AM_PATH_WXCONFIG(2.8.0, wxWin=1)
        if test "$wxWin" != 1; then
        AC_MSG_ERROR([
                wxWidgets must be installed on your system.

                Please check that wx-config is in path, the directory
                where wxWidgets libraries are installed (returned by
                'wx-config --libs' or 'wx-config --static --libs' command)
                is in LD_LIBRARY_PATH or equivalent variable and
                wxWindows version is 2.8.0 or above.
                ])
        fi

CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS"
CXXFLAGS="$CXXFLAGS $WX_CXXFLAGS_ONLY"
CFLAGS="$CFLAGS $WX_CFLAGS_ONLY"
LIBS="$LIBS $WX_LIBS"

AC_SUBST(CPPFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(CFLAGS)
AC_SUBST(LIBS)

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

AC_OUTPUT(Makefile wxMoldeoControls/Makefile moldeocontrols.pc )
