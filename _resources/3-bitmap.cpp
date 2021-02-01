// Drawing graphics with wxWidgets
// Example copied from: https://stackoverflow.com/questions/55877790/wxwidgets-best-control-for-drawing-realtime-graphics

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/dcclient.h>
#include <wx/rawbmp.h>
#include <wx/timer.h>

///////////// Declarations

class MyFrame : public wxFrame {
 public:
  MyFrame(wxWindow* parent, int id = wxID_ANY, wxString title = "Demo",
          wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize,
          int style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
  ~MyFrame();

 private:
  // Event Handlers
  void OnPaint(wxPaintEvent& event);
  void OnTimer(wxTimerEvent& event);

  // Helper function
  void RebuildBufferAndRefresh();

  // Private data
  wxWindow* m_renderSurface;
  int m_width;
  int m_height;
  wxBitmap m_bitmapBuffer;
  wxTimer m_timer;
  int m_curRGB;
  unsigned char* m_pixelData;
};

class MyApp : public wxApp {
 public:
  virtual bool OnInit() wxOVERRIDE;
};

wxDECLARE_APP(MyApp);

///////////// Implementation

MyFrame::MyFrame(wxWindow* parent, int id, wxString title, wxPoint pos,
                 wxSize size, int style)
    : wxFrame(parent, id, title, pos, size, style) {
  m_width = 100;
  m_height = 100;
  m_pixelData = new unsigned char[3 * m_width * m_height];

  m_renderSurface = new wxWindow(this, wxID_ANY, wxDefaultPosition,
                                 wxSize(m_width, m_height));
  m_renderSurface->SetBackgroundStyle(wxBG_STYLE_PAINT);
  m_renderSurface->Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);

  wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);
  bSizer->Add(m_renderSurface, 0);
  this->SetSizer(bSizer);
  Layout();

  m_timer.SetOwner(this);
  m_timer.Start(17);
  this->Bind(wxEVT_TIMER, &MyFrame::OnTimer, this);
  m_curRGB = 0;
}

MyFrame::~MyFrame() {
  m_timer.Stop();
  delete[] m_pixelData;
}

void MyFrame::OnPaint(wxPaintEvent& event) {
  wxPaintDC dc(m_renderSurface);
  if (m_bitmapBuffer.IsOk()) {
    dc.DrawBitmap(m_bitmapBuffer, 0, 0);
  }
}

void MyFrame::OnTimer(wxTimerEvent& event) {
  RebuildBufferAndRefresh();
}

void MyFrame::RebuildBufferAndRefresh() {
  // Build the pixel buffer here, for this simple example just set all
  // pixels to the same value and then increment that value.
  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      m_pixelData[3 * y * m_width + 3 * x] = m_curRGB;
      m_pixelData[3 * y * m_width + 3 * x + 1] = m_curRGB;
      m_pixelData[3 * y * m_width + 3 * x + 2] = m_curRGB;
    }
  }

  ++m_curRGB;
  if (m_curRGB > 255) {
    m_curRGB = 0;
  }

  // Now transfer the pixel data into a wxBitmap
  wxBitmap b(m_width, m_height, 24);
  wxNativePixelData data(b);

  if (!data) {
    // ... raw access to bitmap data unavailable, do something else ...
    return;
  }

  wxNativePixelData::Iterator p(data);

  int curPixelDataLoc = 0;
  for (int y = 0; y < m_height; ++y) {
    wxNativePixelData::Iterator rowStart = p;
    for (int x = 0; x < m_width; ++x, ++p) {
      p.Red() = m_pixelData[curPixelDataLoc++];
      p.Green() = m_pixelData[curPixelDataLoc++];
      p.Blue() = m_pixelData[curPixelDataLoc++];
    }
    p = rowStart;
    p.OffsetY(data, 1);
  }

  m_bitmapBuffer = b;
  m_renderSurface->Refresh();
  m_renderSurface->Update();
}

bool MyApp::OnInit() {
  MyFrame* frame = new MyFrame(NULL);
  frame->Show();
  return true;
}

wxIMPLEMENT_APP(MyApp);