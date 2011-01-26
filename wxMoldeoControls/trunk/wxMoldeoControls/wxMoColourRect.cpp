#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wxMoColourLevelCtrl.h"

#include <wx/file.h>
#include <wx/dcbuffer.h>



wxMoColour::wxMoColour() {
    m_ColourMode = RGBA;
    UpdateColour( wxColour(0,0,0) );

}

wxMoColour::wxMoColour( const wxColour& col, ColourMode mode ) {
    m_ColourMode = mode;
    UpdateColour( col );
}

wxMoColour::wxMoColour( wxColour::ChannelType red, wxColour::ChannelType green, wxColour::ChannelType blue, wxColour::ChannelType alpha ) {

    m_ColourMode = RGBA;
    UpdateColour( wxColour(red,green,blue,alpha) );

}

wxMoColour::wxMoColour( double hue, double saturation, double value, wxColour::ChannelType alpha ) {

    m_HSVValue.hue = hue;
    m_HSVValue.saturation = saturation;
    m_HSVValue.value = value;

    ///internal RGB values
    ///m_RGBValue = wxImage::HSVtoRGB( m_HSVValue );
    ///m_RGBValue = wxImage::HSVtoRGB( m_HSVValue );
    HSVtoRGB( (short)(m_HSVValue.hue*359),
              (short)(m_HSVValue.saturation*255.0),
              (short)(m_HSVValue.value*255.0),
              (float*)&m_RGBDouble.red,
              (float*)&m_RGBDouble.green,
              (float*)&m_RGBDouble.blue );
    m_RGBValue.red = m_RGBDouble.red;
    m_RGBValue.green = m_RGBDouble.green;
    m_RGBValue.blue = m_RGBDouble.blue;

    ///assign now
    m_ColourValue = wxColour( m_RGBValue.red, m_RGBValue.green, m_RGBValue.blue, alpha );
}

wxMoColour::wxMoColour( double hue, double saturation, double value, double alpha )
{
    (*this) = wxMoColour( hue, saturation, value );
    m_Alpha = (unsigned char) std::max( 0, (int)std::min( 255.0, alpha*255.0) );
    m_ColourValue = wxColour( m_RGBValue.red, m_RGBValue.green, m_RGBValue.blue, m_Alpha );
}


wxMoColour::~wxMoColour() {

}

void
wxMoColour::UpdateColour( wxColour p_Colour ) {

  ///internal RGB values
  m_RGBValue.red = p_Colour.Red();
  m_RGBValue.green = p_Colour.Green();
  m_RGBValue.blue = p_Colour.Blue();

  m_RGBDouble.red = m_RGBValue.red / 255.0;
  m_RGBDouble.green = m_RGBValue.green / 255.0;
  m_RGBDouble.blue = m_RGBValue.blue / 255.0;

  ///internal HSV values
  m_HSVValue = wxImage::RGBtoHSV( m_RGBValue );

  ///assign now
  m_ColourValue = p_Colour;
}

void wxMoColour::UpdateColour( wxMoColour p_MoColour ) {

    switch( p_MoColour.Model() ) {

      case RGBA:
        UpdateColour( p_MoColour.m_ColourValue );
        break;

      case HSV:
        ///internal HSV values
        m_HSVValue.hue = p_MoColour.Hue();
        m_HSVValue.saturation = p_MoColour.Saturation();
        m_HSVValue.value = p_MoColour.Value();

        ///internal RGB values
        HSVtoRGB( (short)(m_HSVValue.hue*359),
              (short)(m_HSVValue.saturation*255.0),
              (short)(m_HSVValue.value*255.0),
              (float*)&m_RGBDouble.red,
              (float*)&m_RGBDouble.green,
              (float*)&m_RGBDouble.blue );
        m_RGBValue.red = m_RGBDouble.red;
        m_RGBValue.green = m_RGBDouble.green;
        m_RGBValue.blue = m_RGBDouble.blue;

        ///assign now
        m_ColourValue = wxColour( m_RGBValue.red, m_RGBValue.green, m_RGBValue.blue, p_MoColour.Alpha() );
        break;

    }

}

double wxMoColour::RedNormal() {
    return m_RGBDouble.red;
}

double wxMoColour::GreenNormal() {
    return m_RGBDouble.green;
}

double wxMoColour::BlueNormal() {
    return m_RGBDouble.blue;
}


wxColour::ChannelType wxMoColour::Red()  {
    return m_RGBDouble.red;
}

wxColour::ChannelType wxMoColour::Green()  {
    return m_RGBValue.green;
}

wxColour::ChannelType wxMoColour::Blue()  {
    return m_RGBValue.blue;
}

wxColour::ChannelType wxMoColour::Alpha() {
    return m_Alpha;
}

double wxMoColour::Hue() {
    return m_HSVValue.hue;
}

double wxMoColour::Saturation() {
    return m_HSVValue.saturation;
}

double wxMoColour::Value() {
    return m_HSVValue.value;
}

wxMoColour::ColourMode wxMoColour::Model() {
    return m_ColourMode;
}

wxMoColour::ColourMode wxMoColour::Mode() {
    return m_ColourMode;
}



BEGIN_EVENT_TABLE( wxMoColourLevelCtrl, wxMoLevelCtrl )
    EVT_PAINT( wxMoColourLevelCtrl::OnPaint )
END_EVENT_TABLE()

wxMoColourLevelCtrl::wxMoColourLevelCtrl( wxWindow* parent, wxWindowID id, const int value, const int minvalue, const int maxvalue, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name  ) :
wxMoLevelCtrl( parent, id, value, minvalue, maxvalue, pos, size, style | wxNO_BORDER, validator, name ) {

        m_Init = false;

        m_min = 0;
        m_max = 255;
        m_value = value;

        m_RGBValue.red = 0;
        m_RGBValue.green = 0;
        m_RGBValue.blue = 0;

        m_HSVValue.hue = 0.0f;
        m_HSVValue.saturation = 0.0f;
        m_HSVValue.value = 0.0f;

        m_pRedLevel = NULL;
        m_pGreenLevel = NULL;
        m_pBlueLevel = NULL;

        m_pHueLevel = NULL;
        m_pSaturationLevel = NULL;
        m_pValueLevel = NULL;

        m_pAlphaLevel = NULL;

        ///initialize in one channel
        /// better is light

        ///Init( RED );

}

wxMoColourLevelCtrl::~wxMoColourLevelCtrl() {


}


void
wxMoColourLevelCtrl::UpdatePattern() {


    ///Get control size
    wxSize sz = GetSize();
    wxMemoryDC mdc;
    int i,j;
    double delta;
    wxImage::HSVValue HSVVal,HSVVal1,HSVVal2;
    wxImage::RGBValue RGBVal;

    if (!m_Pattern.IsOk()) {
      wxMessageBox(wxString("moWxMoColorLevelCtrl UpdatePattern error - IsOk not ok!! "));
    } else {

      ///intialize memory dc to the bitmap
      mdc.SelectObject( m_Pattern );
      mdc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );
      HSVVal = HSVVal1 = HSVVal2 = m_HSVValue;

      switch (m_ColourChannel) {

       case HUE:
          /// the crominance pattern from 0g (left) to 359g (right)
          //HSVVal.value = 1.0;
          //HSVVal.saturation = 1.0;

          HSVVal1.hue = 0.0;
          HSVVal2.hue = MAX_HUE_FLOAT;
          delta = (HSVVal2.hue - HSVVal1.hue) / ( sz.GetWidth()-1 );

          for( i=0; i<sz.GetWidth(); i++) {
            HSVVal.hue = i * delta;
            HSVVal2 = HSVVal;
            HSVVal2.saturation = 1.0;
            HSVVal2.value = 1.0;

            ///first we draw the full saturated spectrum
            RGBVal = wxImage::HSVtoRGB(HSVVal2);
            mdc.SetBrush( wxBrush( wxColour( RGBVal.red, RGBVal.green, RGBVal.blue ), wxSOLID) );
            mdc.DrawRectangle( i, 0, 1, sz.GetHeight() );

            ///then the actual saturation spectrum
            RGBVal = wxImage::HSVtoRGB(HSVVal);
            mdc.SetBrush( wxBrush( wxColour( RGBVal.red, RGBVal.green, RGBVal.blue ), wxSOLID) );
            mdc.DrawRectangle( i, 2, 1, sz.GetHeight()-4 );
          }

          break;

        case SATURATION:
          ///no saturation to full saturation
          HSVVal1.saturation = 0.0;
          HSVVal2.saturation = 1.0;
          delta = (HSVVal2.saturation - HSVVal1.saturation) / ( sz.GetWidth() -1 );

          for( i=0; i<sz.GetWidth(); i++) {
            HSVVal.saturation = i * delta;
            RGBVal = wxImage::HSVtoRGB(HSVVal);
            mdc.SetBrush( wxBrush( wxColour( RGBVal.red, RGBVal.green, RGBVal.blue ), wxSOLID) );
            mdc.DrawRectangle( i, 0, 1, sz.GetHeight() );
          }
          break;

        case VALUE:
          ///value from 0 to 1 (max)
          HSVVal1.value = 0.0;
          HSVVal2.value = 1.0;
          delta = (HSVVal2.value - HSVVal1.value) / ( sz.GetWidth() -1 );

          for( i=0; i<sz.GetWidth(); i++) {
            HSVVal.value = i * delta;
            RGBVal = wxImage::HSVtoRGB(HSVVal);
            mdc.SetBrush( wxBrush( wxColour( RGBVal.red, RGBVal.green, RGBVal.blue ), wxSOLID) );
            mdc.DrawRectangle( i, 0, 1, sz.GetHeight() );
          }
          break;
      }

    }

}

void
wxMoColourLevelCtrl::CreatePattern() {

    ///Get control size
    wxSize sz = GetSize();
    wxImage PatternImage;

    switch (m_ColourChannel) {

      case ALPHA:

        ///this is a transparent gradient from full transparent color (left)
        /// to full opaque color (right)
        if (wxFile::Exists("art/icons/patron96.png")) {
          PatternImage = wxImage("art/icons/patron96.png");
        }
        else if (wxFile::Exists("../../art/icons/patron96.png")) {
          PatternImage = wxImage("../../art/icons/patron96.png");
        } else {
            wxMessageBox(wxString("wxMoColourLevelCtrl::Init error > Alpha Transparent Image Pattern \"patron96.png\" not found !"));
        }

        if ( PatternImage.IsOk() ) {
          PatternImage.Rescale( sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH );
          m_Pattern = wxBitmap( PatternImage );
        }
        break;

      case HUE:
      case SATURATION:
      case VALUE:
        ///create now, update dynamically
        if (!m_Pattern.Create( sz.GetWidth(), sz.GetHeight(), 24 )) {
            wxMessageBox(wxString("wxMoColourLevelCtrl error creating pattern bitmap."));
        }
        break;
    }


}

void
wxMoColourLevelCtrl::Init( ColourChannel p_channel ) {

    ///assign the colour channel
    m_ColourChannel = p_channel;

    ///assign the colour mode
    ((m_ColourChannel==RED)||(m_ColourChannel==GREEN)||(m_ColourChannel==BLUE)||(m_ColourChannel==ALPHA)) ? m_ColourMode = RGBA : m_ColourMode = HSV;

    switch (m_ColourChannel) {
      case HUE:
        m_max = MAX_HUE;
        break;
      case SATURATION:
        m_max = MAX_SATURATION;
        break;
      case VALUE:
        m_max = MAX_VALUE;
        break;
      case RED:
        m_max = MAX_RED;
        break;
      case GREEN:
        m_max = MAX_GREEN;
        break;
      case BLUE:
        m_max = MAX_BLUE;
        break;
      case ALPHA:
        m_max = MAX_ALPHA;
        break;
    }

    ///assign the pattern image
    CreatePattern();

    m_Init = true;

    SetColourValue( wxColour( 0 , 0, 0, 0 ) );

}

void
wxMoColourLevelCtrl::SetColourValue( wxColour p_ColourValue, bool propagate ) {

  ///necesarry to map m_ColourValue internally to RGB and HSV
  UpdateColour( p_ColourValue );

  ///internal process of colour
  ProcessColour();

  if (propagate) {
      Propagate();
  }

}

wxColour
wxMoColourLevelCtrl::GetColourValue() {

  return m_ColourValue;

}



void
wxMoColourLevelCtrl::OnPaint(wxPaintEvent& event) {

    wxBufferedPaintDC dc(this);

    wxPoint Triangle[3];

    dc.SetBrush( wxBrush( wxColour(80,80,80), wxSOLID ) );

    if ( (this) == FindFocus() ) {
        dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    } else dc.SetPen( wxPen( wxColour(255,255,255), 1, wxTRANSPARENT ) );

    ///background
    dc.DrawRectangle( 0, 0, GetSize().x, GetSize().y );
    dc.GradientFillLinear( wxRect(0, 0, GetSize().x, GetSize().y), m_ColourMin, m_ColourMax, wxEAST );

    if (m_Pattern.IsOk()) {
        if ( m_ColourChannel==ALPHA || m_ColourMode == HSV ) {
          dc.DrawBitmap( m_Pattern,  0, 0, true );
        }
    }

    ///gauge
    //dc.SetBrush( wxBrush( wxColour(0,200,50,25), wxTRANSPARENT) );
    //dc.SetPen( wxPen( wxColour(140,140,140,25), 1, wxTRANSPARENT ) );
    //dc.DrawRectangle( 1, 1, SlidePosition()-2, GetSize().y-2 );
    //wxRect Rgauge( 1, 1, SlidePosition()-2, GetSize().y-2 );

    //dc.GradientFillLinear( Rgauge, wxColour(80,150,80), wxColour(0,255,0), wxBOTTOM );
    //dc.GradientFillLinear( Rgauge, m_ColourMin, m_ColourMax, wxBOTTOM );

    ///COLOR mark
    dc.SetBrush( wxBrush( wxColour(0,0,0), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    Triangle[0].x = SlidePosition();
    Triangle[0].y = GetSize().y - 4;
    Triangle[1].x = SlidePosition()-4;
    Triangle[1].y = GetSize().y;
    Triangle[2].x = SlidePosition()+4;
    Triangle[2].y = GetSize().y;
    dc.DrawPolygon( 3, Triangle, 0, 0 );

    dc.SetBrush( wxBrush( wxColour(255,255,255), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(0,0,0), 1, wxSOLID ) );
    Triangle[0].x = SlidePosition();
    Triangle[0].y = 4;
    Triangle[1].x = SlidePosition()-4;
    Triangle[1].y = 0;
    Triangle[2].x = SlidePosition()+4;
    Triangle[2].y = 0;
    dc.DrawPolygon( 3, Triangle, 0, 0 );


    ///ticks
    dc.SetBrush( wxBrush( wxColour(128,128,128), wxSOLID ) );
    dc.SetPen( wxPen( wxColour(255,255,255), 1, wxSOLID ) );
    int nticks = 5;
    int dticks = (GetSize().x / nticks );
    int ysize;

    /*

    for(int i =0; i<nticks; i++ ) {
        ( i % 3 ) == 0 ? ysize = GetSize().y / 2 : ysize = GetSize().y / 3;
        dc.DrawLine( i*dticks, ysize, i*dticks, GetSize().y );
    }
    */

    ///text

/*
    wxString deb;
    deb.Printf(GetName()+_T(": %i"),GetSize().GetX());
    dc.DrawText(deb,20,0);
*/
    wxString s;
    wxString d;
    wxSize textsize;

    dc.SetFont(wxFont( 8,  wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ) );
    dc.SetTextForeground( wxColour(155,0,0) );

    switch( m_ColourChannel ) {
      case HUE:
      case SATURATION:
      case VALUE:
        d.Printf( "h:%2.2f s:%2.2f v:%2.2f", m_HSVValue.hue, m_HSVValue.saturation, m_HSVValue.value );
        break;
    }

    //textsize = dc.GetTextExtent(d);
    //dc.DrawText( d, 0, 0 );


    if (m_Init) {
      dc.SetTextForeground( wxColour(255,255,255) );
      if (m_bStartDragging) {
        s.Printf( "%i", m_value);
      } else {
        s.Printf("");
      }
    } else s.Printf("need init");

    textsize = dc.GetTextExtent(s);
    dc.DrawText( s, (GetSize().x/2) - (textsize.x/2), 0 );

    //}
}


///internal process of colour
void
wxMoColourLevelCtrl::ProcessColour() {

  double hsv_val = 0.0f;

  ///update internals!!
  /// slide value, (m_value)
  /// min and max colours,
  /// hsv patterns
  switch( m_ColourChannel ) {

        case RED:
          m_value = m_ColourValue.Red();
          m_ColourMin = wxColour( m_min, m_ColourValue.Green(), m_ColourValue.Blue(), m_ColourValue.Alpha() );
          m_ColourMax = wxColour( m_max, m_ColourValue.Green(), m_ColourValue.Blue(), m_ColourValue.Alpha() );
          break;
        case GREEN:
          m_value = m_ColourValue.Green();
          m_ColourMin = wxColour( m_ColourValue.Red(), m_min, m_ColourValue.Blue(), m_ColourValue.Alpha()  );
          m_ColourMax = wxColour( m_ColourValue.Red(), m_max, m_ColourValue.Blue(), m_ColourValue.Alpha()  );
          break;
        case BLUE:
          m_value = m_ColourValue.Blue();
          m_ColourMin = wxColour( m_ColourValue.Red(), m_ColourValue.Green(), m_min, m_ColourValue.Alpha() );
          m_ColourMax = wxColour( m_ColourValue.Red(), m_ColourValue.Green(), m_max, m_ColourValue.Alpha() );
          break;
        case ALPHA:
          m_value = m_ColourValue.Alpha();
          m_ColourMin = wxColour( m_ColourValue.Red(), m_ColourValue.Green(), m_ColourValue.Blue(), m_min );
          m_ColourMax = wxColour( m_ColourValue.Red(), m_ColourValue.Green(), m_ColourValue.Blue(), m_max );
          break;

        case HUE:
          hsv_val = m_HSVValue.hue * (double) (m_max + 1);
          m_value = (int) hsv_val;
          ///m_ColourMin = wxColour( m_min, m_min, m_min, 255 );
          ///m_ColourMax = wxColour( m_max, m_max, m_max, 255 );
          ///has to draw it with a bitmap
          UpdatePattern();
          break;

        case SATURATION:

          hsv_val = m_HSVValue.saturation * (double) m_max;
          m_value = (int) hsv_val;
          ///m_ColourMin = wxColour( m_min, m_min, m_min, 255 );
          ///m_ColourMax = wxColour( m_max, m_max, m_max, 255 );
          ///has to draw it with a bitmap to
          UpdatePattern();
          break;

        case VALUE:
          hsv_val = m_HSVValue.value * (double) m_max;
          m_value = (int) hsv_val;
          ///m_ColourMin = wxColour( 0, 0, 0, m_ColourValue.Alpha() );
          ///m_ColourMax = wxColour( m_ColourValue.Red(), m_max, m_max, m_ColourValue.Alpha() );
          ///has to draw it with a bitmap to
          UpdatePattern();
          break;

        default:
          break;
    }

  ///IMPORTANT ! to reflect changes!!!
  Refresh();
}

void
wxMoColourLevelCtrl::Propagate() {

      ///never pass the propagate parameter to other controls
      ///can loop infinite if missuse
      ///neither can do any self propagation

      if ( m_pRedLevel && ( m_ColourChannel!=RED ) && (m_pRedLevel!=this)) {
        m_pRedLevel->SetColourValue( m_ColourValue );
      }

      if ( m_pGreenLevel && ( m_ColourChannel!=GREEN ) && (m_pGreenLevel!=this) ) {
        m_pGreenLevel->SetColourValue( m_ColourValue );
      }

      if ( m_pBlueLevel && ( m_ColourChannel!=BLUE ) && (m_pBlueLevel!=this) ) {
        m_pBlueLevel->SetColourValue( m_ColourValue );
      }

      if ( m_pAlphaLevel && ( m_ColourChannel!=ALPHA ) && (m_pAlphaLevel!=this) ) {
        m_pAlphaLevel->SetColourValue( m_ColourValue );
      }

      if ( m_pHueLevel && ( m_ColourChannel!=HUE ) && (m_pHueLevel!=this) ) {
        m_pHueLevel->SetColourValue( m_ColourValue );
      }

      if ( m_pSaturationLevel && ( m_ColourChannel!=SATURATION ) && (m_pSaturationLevel!=this) ) {
        m_pSaturationLevel->SetColourValue( m_ColourValue );
      }

      if ( m_pValueLevel && ( m_ColourChannel!=VALUE ) && (m_pValueLevel!=this) ) {
        m_pValueLevel->SetColourValue( m_ColourValue );
      }

}

///this function is called when the own slide position has change or the value has been set externally by SetValue
void wxMoColourLevelCtrl::ChangeValue( int value ) {
    if (value<=m_min) value = m_min;
    if (value>m_max) value = m_max;

    this->m_value = value;

    ///here we do propagate!!!
    switch( m_ColourChannel ) {
      case RED:
        SetRedValue(m_value, true);
        break;
      case GREEN:
        SetGreenValue(m_value, true);
        break;
      case BLUE:
        SetBlueValue(m_value, true);
        break;
      case ALPHA:
        SetAlphaValue(m_value, true);
        break;
      case HUE:
        SetHueValue(m_value, true);
        break;
      case SATURATION:
        SetSaturationValue(m_value, true);
        break;
      case VALUE:
        SetValueValue(m_value, true);
        break;
      default:
        break;
    }

    Refresh();
}


void
wxMoColourLevelCtrl::SetMinColor( wxColour p_min_color ) {

  m_ColourMin = p_min_color;

}

void
wxMoColourLevelCtrl::SetMaxColor( wxColour p_max_color ) {

  m_ColourMax = p_max_color;

}


/**

  RGBA

*/

void
wxMoColourLevelCtrl::SetRedValue( wxColour::ChannelType p_red_value, bool propagate ) {
  SetColourValue( wxColour( p_red_value, m_ColourValue.Green(), m_ColourValue.Blue(), m_ColourValue.Alpha() ), propagate );
}

void
wxMoColourLevelCtrl::SetGreenValue( wxColour::ChannelType p_green_value, bool propagate  ) {
  SetColourValue( wxColour( m_ColourValue.Red(), p_green_value, m_ColourValue.Blue(), m_ColourValue.Alpha() ), propagate );
}

void
wxMoColourLevelCtrl::SetBlueValue( wxColour::ChannelType p_blue_value, bool propagate ) {
  SetColourValue( wxColour( m_ColourValue.Red(), m_ColourValue.Green(), p_blue_value, m_ColourValue.Alpha() ), propagate );
}

void
wxMoColourLevelCtrl::SetAlphaValue( wxColour::ChannelType p_alpha_value, bool propagate ) {
  SetColourValue( wxColour( m_ColourValue.Red(), m_ColourValue.Green(), m_ColourValue.Blue(), p_alpha_value ), propagate );
}

/**

  HSV

*/

void
wxMoColourLevelCtrl::SetHueValue( unsigned int p_hue_value, bool propagate ) {

  ///just to be sure RGB and HSV are updated
  UpdateColour( m_ColourValue );

  double hsv_d = ((double) (p_hue_value)) / (double)(MAX_HUE);
  if (hsv_d>MAX_HUE_FLOAT) hsv_d = MAX_HUE_FLOAT;
  m_HSVValue.hue = hsv_d;
  m_RGBValue = wxImage::HSVtoRGB( m_HSVValue );

  SetColourValue( wxColour( m_RGBValue.red, m_RGBValue.green, m_RGBValue.blue, m_ColourValue.Alpha() ), propagate );
}


void
wxMoColourLevelCtrl::SetSaturationValue( wxColour::ChannelType p_saturation_value, bool propagate ) {

  ///just to be sure RGB and HSV are updated
  UpdateColour( m_ColourValue );

  double hsv_d = ((double) (p_saturation_value)) / (double)(MAX_SATURATION);
  m_HSVValue.saturation = hsv_d;
  m_RGBValue = wxImage::HSVtoRGB( m_HSVValue );

  SetColourValue( wxColour( m_RGBValue.red, m_RGBValue.green, m_RGBValue.blue, m_ColourValue.Alpha() ), propagate );

}


void
wxMoColourLevelCtrl::SetValueValue( wxColour::ChannelType p_value_value, bool propagate ) {

  ///just to be sure RGB and HSV are updated
  UpdateColour( m_ColourValue );

  double hsv_d = ((double) (p_value_value)) / (double)(MAX_VALUE);
  m_HSVValue.value = hsv_d;
  m_RGBValue = wxImage::HSVtoRGB( m_HSVValue );

  SetColourValue( wxColour( m_RGBValue.red, m_RGBValue.green, m_RGBValue.blue, m_ColourValue.Alpha() ), propagate );

}



/**

      CONTROLS INTERACTIONS


*/



void
wxMoColourLevelCtrl::SetRGBAColorComponents(   wxMoColourLevelCtrl* p_red_level,
                                              wxMoColourLevelCtrl* p_green_level,
                                              wxMoColourLevelCtrl* p_blue_level,
                                              wxMoColourLevelCtrl* p_alpha_level ) {

  if (p_red_level && (p_red_level->GetColourChannel()==RED) && (p_red_level!=this)) m_pRedLevel = p_red_level;
  if (p_green_level && (p_green_level->GetColourChannel()==GREEN) && (p_green_level!=this)) m_pGreenLevel = p_green_level;
  if (p_blue_level && (p_blue_level->GetColourChannel()==BLUE) && (p_blue_level!=this)) m_pBlueLevel = p_blue_level;
  if (p_alpha_level && (p_alpha_level->GetColourChannel()==ALPHA) && (p_alpha_level!=this)) m_pAlphaLevel = p_alpha_level;

}


void
wxMoColourLevelCtrl::SetHSVColorComponents(  wxMoColourLevelCtrl* p_hue_level,
                                            wxMoColourLevelCtrl* p_saturation_level,
                                            wxMoColourLevelCtrl* p_value_level ) {

  if (p_hue_level && (p_hue_level->GetColourChannel()==HUE) && (p_hue_level!=this)) m_pHueLevel = p_hue_level;
  if (p_saturation_level && (p_saturation_level->GetColourChannel()==SATURATION) && (p_saturation_level!=this)) m_pSaturationLevel = p_saturation_level;
  if (p_value_level && (p_value_level->GetColourChannel()==VALUE) && (p_value_level!=this)) m_pValueLevel = p_value_level;

}

DEFINE_EVENT_TYPE(wxEVT_MOCOLORLEVELCTRL)
