#include "wx/wx.h"

class mFrame : public wxFrame {
 public:
  mFrame();
  ~mFrame();
};

mFrame::mFrame()
    : wxFrame(nullptr, wxID_ANY, "Crawler bot", wxPoint(250, 200),
              wxSize(900, 360)) {}

mFrame::~mFrame() {}

class MyApp : public wxApp {
 private:
  mFrame *m_frame = nullptr;

 public:
  MyApp();
  ~MyApp();

  virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
  m_frame = new mFrame();
  m_frame->SetMaxSize(wxSize(900, 360));
  m_frame->SetMinSize(wxSize(900, 360));
  m_frame->Update();
  m_frame->Refresh();
  m_frame->CreateStatusBar();
  m_frame->SetStatusText("Crawler bot");

  m_frame->Show();

  return true;
}

MyApp::MyApp() {}
MyApp::~MyApp() {}