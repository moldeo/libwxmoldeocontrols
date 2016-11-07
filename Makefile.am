ACLOCAL_AMFLAGS=-I m4

if DEBUG
DFLAGS = -g3 -O0 -fpermissive
else
DFLAGS = -O2 -fpermissive
endif
SUBDIRS = wxMoldeoControls wxMoldeoControlsTest

EXTRA_DIST = AUTHORS ChangeLog NEWS README

# pkg-config stuff, note that libpng.pc is always required in order
# to get the correct library
pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = moldeocontrols.pc

datadir = ${prefix}/share/moldeo/data
docdir = ${prefix}/share/doc/moldeo/wxMoldeoControls
cursorsdir = ${datadir}/cursors
fontsdir = ${datadir}/fonts
iconsdir = ${datadir}/icons

dist_doc_DATA = README

AM_CPPFLAGS = -DMCONTROLSDATADIR=\"$(datadir)\"

