#include "WxMoGLCanvas.h"

#include <wx/dcclient.h>
#include <wx/msgdlg.h>

BEGIN_EVENT_TABLE(wxMoGLCanvas, wxGLCanvas)
   // EVT_TIMER( TIMER_ID, moGLCanvas::OnTimer)
   // EVT_SIZE(moGLCanvas::OnSize)
	//EVT_CLOSE(moGLCanvas::OnClose)
    EVT_PAINT(wxMoGLCanvas::OnPaint)
    //EVT_ERASE_BACKGROUND(moGLCanvas::OnEraseBackground)
    //EVT_MOUSE_EVENTS(moGLCanvas::OnMouse)
	//EVT_KEY_DOWN( moGLCanvas::OnKeyDown )
	//EVT_KEY_UP( moGLCanvas::OnKeyUp )
END_EVENT_TABLE()

wxMoGLCanvas::wxMoGLCanvas(wxWindow *parent,
    wxWindowID id,
    int* attribList,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name, attribList, wxNullPalette)
{
	//m_init = false;
    //block = false;
    //m_active = false;
	//m_pHandler = NULL;
	//SetCursor(wxCursor(wxCURSOR_BLANK));


}
void wxMoGLCanvas::Init() {
    int w, h;
    GetClientSize(&w, &h);

   // wxGLCanvas::SetCurrent();
/*
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong.
		//MODebug2->Error(moText("GLEW Error: ")+ moText((char*)glewGetErrorString(err)));
		wxMessageBox(wxString("2-")+wxString(glewGetErrorString(err)));
		//cout << glewGetErrorString(err) << endl;


	} else {
	    wxMessageBox("2- ok");
    }
*/


   // set background-color
   glClearColor(1.0, 0.0, 0.0, 0.0);

   // set the quality of the interpolation of color and texture
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

   // set the samplequality of the interpolation of color and texture
   glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

   // activate depth-buffer for depth-compare
   glEnable(GL_DEPTH_TEST);

   // flat-mode for primitives
   glShadeModel(GL_FLAT);

}

void wxMoGLCanvas::Render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor4f( 0.0, 1.0, 0.0, 1.0);
    glDisable( GL_TEXTURE_2D );
    glBegin(GL_QUADS);
        glVertex2d(0.0,0.0);
        glVertex2d(0.5,1.0);
        glVertex2d(0.9,1.0);
        glVertex2d(1.0,0.0);
    glEnd();

    SwapBuffers();


}

void wxMoGLCanvas::OnPaint(wxPaintEvent& event) {

    wxGLCanvas::SetCurrent();

    wxPaintDC dc(this);
    int w, h;
    GetClientSize(&w, &h);

    /*if( GetContext() )
    if (!m_init && !block) {
        SetView(0,0,w,h);
        Log("GL Canvas Initialized");
        m_init = true;
    }*/
    Render();
}
