ACLOCAL_AMFLAGS=-I m4
SUBDIRS = wxMoldeoControls

EXTRA_DIST = AUTHORS ChangeLog NEWS README

# pkg-config stuff, note that libpng.pc is always required in order
# to get the correct library
pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = moldeocontrols.pc

datadir = ${prefix}/share/wxMoldeoControls
docdir = ${prefix}/share/doc/wxMoldeoControls
cursorsdir = ${datadir}/cursors
fontsdir = ${datadir}/fonts
iconsdir = ${datadir}/icons

dist_doc_DATA = README

AM_CPPFLAGS = -DMCONTROLSDATADIR=\"$(datadir)\"

