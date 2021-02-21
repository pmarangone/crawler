#include "wx/wx.h"
#include <wx/spinctrl.h>

const int winWidth = 900, winHeight = 360;

class MySpin {
 public:
  MySpin();
  MySpin(wxPanel *panel, wxStandardID id, double precision, double increment,
         double initialValue);
  ~MySpin();

  wxSpinCtrlDouble *Get();

  wxSpinCtrlDouble *ctrlSpin = nullptr;
  double minValue, maxValue;
};

MySpin::MySpin() {}
MySpin::~MySpin() {}

MySpin::MySpin(wxPanel *panel, wxStandardID id, double precision,
               double increment, double initialValue)
    : ctrlSpin(new wxSpinCtrlDouble(panel, id)),
      minValue(INT_MIN),
      maxValue(INT_MAX) {
  // ctrlSpin = new wxSpinCtrlDouble(panel, id);
  ctrlSpin->SetDigits(precision);
  ctrlSpin->SetIncrement(increment);
  ctrlSpin->SetValue(initialValue);
  ctrlSpin->SetRange(minValue, maxValue);
}

wxSpinCtrlDouble *MySpin::Get() { return ctrlSpin; }

class mFrame : public wxFrame {
 public:
  mFrame();
};

mFrame::mFrame()
    : wxFrame(nullptr, wxID_ANY, "Crawler bot", wxPoint(250, 200),
              wxSize(winWidth, winHeight)) {
  SetMaxSize(wxSize(winWidth, winHeight));
  SetMinSize(wxSize(winWidth, winHeight));

  wxPanel *panel =
      new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));

  // Bottom sizer (nested)
  wxBoxSizer *sizerBottomCV = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *sizerBottomCH = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *sizerMain = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sizerSecond = new wxBoxSizer(wxHORIZONTAL);

  wxSpinCtrlDouble *ctrlMain = new wxSpinCtrlDouble(panel, wxID_ANY);
  ctrlMain->SetDigits(3);
  ctrlMain->SetIncrement(0.05);
  ctrlMain->SetValue(1);

  // wxSpinCtrlDouble *ctrlSecond = new wxSpinCtrlDouble(panel, wxID_ANY);
  // ctrlSecond->SetDigits(3);
  // ctrlSecond->SetIncrement(0.05);
  // ctrlSecond->SetValue(1);

  wxSpinCtrlDouble *ctrlSecond =
      (new MySpin(panel, wxID_ANY, 3, 0.05, 1))->Get();

  sizerMain->Add(ctrlMain, 0, wxALIGN_CENTER, 0);
  sizerSecond->Add(ctrlSecond, 0, wxALIGN_CENTER, 0);

  sizerBottomCH->Add(sizerMain, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerBottomCH->Add(sizerSecond, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  sizerBottomCV->Add(sizerBottomCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  panel->SetSizerAndFit(sizerBottomCV);
}

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
  m_frame->Show();
  return true;
}

MyApp::MyApp() {}
MyApp::~MyApp() {}