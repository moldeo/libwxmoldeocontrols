ACLOCAL_AMFLAGS=-I m4

AM_CPPFLAGS = $(all_includes) 
AM_CXXFLAGS = $(all_includes)

lib_LTLIBRARIES = libmoldeocontrols.la


libmoldeocontrols_la_SOURCES = wxMoldeoControls.h\
wxMoAuiTabArt.cpp\
wxMoAuiTabArt.h\
wxMoColour.cpp\
wxMoColour.h\
wxMoColourLevelCtrl.cpp\
wxMoColourLevelCtrl.h\
wxMoColourPanel.cpp\
wxMoColourPanel.h\
wxMoldeoLineCtrl.cpp\
wxMoldeoLineCtrl.h\
wxMoldeoObjectCanvas.cpp\
wxMoldeoObjectCanvas.h\
wxMoldeoObjectCtrl.cpp\
wxMoldeoObjectCtrl.h\
wxMoldeoPinCtrl.cpp\
wxMoldeoPinCtrl.h\
wxMoLevelCtrl.cpp\
wxMoLevelCtrl.h\
wxMoRotaryCtrl.cpp\
wxMoRotaryCtrl.h\
wxMoTimelineBandCtrl.cpp\
wxMoTimelineBandCtrl.h\
wxMoTimelineRulerCtrl.cpp\
wxMoTimelineRulerCtrl.h


libmoldeocontrols_la_CPPFLAGS = `pkg-config --cflags gtk+-2.0` \
	${WX_CFLAGS} 

libmoldeocontrols_la_LIBADD = 	${WX_LIBS}

libmoldeocontrols_includedir = $(includedir)/wxMoldeoControls

libmoldeocontrols_include_HEADERS = wxMoldeoControls.h\
wxMoAuiTabArt.h\
wxMoColour.h\
wxMoColourLevelCtrl.h\
wxMoColourPanel.h\
wxMoldeoLineCtrl.h\
wxMoldeoObjectCanvas.h\
wxMoldeoObjectCtrl.h\
wxMoldeoPinCtrl.h\
wxMoLevelCtrl.h\
wxMoRotaryCtrl.h\
wxMoTimelineBandCtrl.h\
wxMoTimelineRulerCtrl.h

METASOURCES = AUTO

