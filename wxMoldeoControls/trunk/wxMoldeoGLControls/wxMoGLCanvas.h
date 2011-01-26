
#ifndef _WXMOGLCANVAS_
#define _WXMOGLCANVAS_
#include "GL/glew.h"
#include <wx/glcanvas.h>

class wxMoGLCanvas: public wxGLCanvas {

public:

    wxMoGLCanvas(wxWindow *parent,
        wxWindowID id = wxID_ANY,
        int* attribList = 0,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0,
        const wxString& name = wxT("wxMoGLCanvas"));

    void Init();
    void OnPaint(wxPaintEvent& event);
    void Render();

    DECLARE_EVENT_TABLE()

};

#endif
