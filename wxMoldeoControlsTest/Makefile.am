ACLOCAL_AMFLAGS=-I m4

if DEBUG
DFLAGS = -g3 -O0 -fpermissive
else
DFLAGS = -O2 -fpermissive
endif

desktopdir = ${prefix}/share/applications
datadir = ${prefix}/share/wxMoldeoControls
docdir = ${prefix}/share/doc/wxMoldeoControls
cursorsdir = ${datadir}/cursors
fontsdir = ${datadir}/fonts
iconsdir = ${datadir}/icons

AM_CPPFLAGS = $(all_includes) -I../wxMoldeoControls -DMCONTROLSDATADIR=\"$(datadir)\"
AM_CXXFLAGS = $(all_includes) -I../wxMoldeoControls -DMCONTROLSDATADIR=\"$(datadir)\"

bin_PROGRAMS = moldeocontrolstest

dist_data_DATA = moldeologo.png moldeocontrolstest.png

dist_desktop_DATA = moldeocontrolstest.desktop

moldeocontrolstest_SOURCES = wxMoldeoControlsTestApp.h\
	wxMoldeoControlsTestDialog.h\
	wxMoldeoControlsTestApp.cpp\
	wxMoldeoControlsTestDialog.cpp

moldeocontrolstest_CPPFLAGS = ${LIBWXMOLDEOCONTROLS_CFLAGS} \
	${WX_CFLAGS} 

moldeocontrolstest_LDFLAGS = ${LIBWXMOLDEOCONTROLS_LDFLAGS}

moldeocontrolstest_LDADD = \
	${LIBWXMOLDEOCONTROLS_LIBS} \
	${WX_LIBS}


