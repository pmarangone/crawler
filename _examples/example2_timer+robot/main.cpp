/* 
 * initial code: https://wiki.wxwidgets.org/Making_a_render_loop 
 */

#define _USE_MATH_DEFINES

#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/wx.h>

#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>

class BasicDrawPane;
const int winWidth = 800;
const int winHeight = 600;


class RenderTimer : public wxTimer {
  BasicDrawPane* pane;

 public:
  RenderTimer(BasicDrawPane* pane);
  void Notify();
  void start();
};

class BasicDrawPane : public wxPanel {
 public:
  BasicDrawPane(wxFrame* parent);

  void paintEvent(wxPaintEvent& evt);
  void paintNow();
  void render(wxDC& dc);

  DECLARE_EVENT_TABLE()
};

class MyFrame;

class MyApp : public wxApp {
  bool OnInit();

  MyFrame* frame;

 public:
};

RenderTimer::RenderTimer(BasicDrawPane* pane) : wxTimer() {
  RenderTimer::pane = pane;
}

void RenderTimer::Notify() {
  pane->Refresh();
}

void RenderTimer::start() {
  wxTimer::Start(10);
}

IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame {
  RenderTimer* timer;
  BasicDrawPane* drawPane;

 public:
  MyFrame() : wxFrame((wxFrame*)NULL, -1, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(winWidth, winHeight)) {
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    drawPane = new BasicDrawPane(this);
    sizer->Add(drawPane, 1, wxEXPAND);
    SetSizer(sizer);

    timer = new RenderTimer(drawPane);
    Show();
    timer->start();
  }
  ~MyFrame() {
    delete timer;
  }
  void onClose(wxCloseEvent& evt) {
    timer->Stop();
    evt.Skip();
  }
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_CLOSE(MyFrame::onClose)
END_EVENT_TABLE()

bool MyApp::OnInit() {
  frame = new MyFrame();
  frame->Show();

  return true;
}

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()

BasicDrawPane::BasicDrawPane(wxFrame* parent) : wxPanel(parent) {
}

void BasicDrawPane::paintEvent(wxPaintEvent& evt) {
  wxPaintDC dc(this);
  render(dc);
}

void BasicDrawPane::paintNow() {
  wxClientDC dc(this);
  render(dc);
}

int groundHeight = 40;
int groundY = winHeight - groundHeight;

double _armAngle = 0.0;
double _handAngle = -M_PI / 6;
double _robotWidth = 80;
double _robotHeight = 40;
double _armLength = 60;
double _handLength = 40;

double _robotPos_x = 20;
double _robotPos_y = groundY;

std::pair<double, double> GetCosAndSin(double angle) {
  double cosine = std::cos(angle);
  double sine = std::sin(angle);
  return std::pair<double, double>(cosine, sine);
}

double GetRotationAngle() {
  double armCos, armSin, handCos, handSin;
  std::tie(armCos, armSin) = GetCosAndSin(_armAngle);
  std::tie(handCos, handSin) = GetCosAndSin(_handAngle);

  double x = _armLength * armCos + _handLength * handCos + _robotWidth;
  double y = _armLength * armSin + _handLength * handSin + _robotHeight;

  if (y < 0) {
    return atan(-y / x);
  }
  return 0.0;
}

void BasicDrawPane::render(wxDC& dc) {
  int x1 = _robotPos_x, y1 = _robotPos_y;
  x1 = x1 % winWidth;

  double rotationAngle = GetRotationAngle();
  double cosRot, sinRot;
  std::tie(cosRot, sinRot) = GetCosAndSin(rotationAngle);

  assert((y1 == groundY) && "Value initialization inconsistent");

  int x2 = x1 + _robotWidth * cosRot;
  int y2 = y1 - _robotWidth * sinRot;

  int x3 = x1 - _robotHeight * sinRot;
  int y3 = y1 - _robotHeight * cosRot;

  int x4 = x3 + cosRot * _robotWidth;
  int y4 = y3 - sinRot * _robotWidth;

  wxPoint points[4];
  points[0] = wxPoint(x1, y1);
  points[1] = wxPoint(x2, y2);
  points[2] = wxPoint(x4, y4);
  points[3] = wxPoint(x3, y3);

  /* ground */
  dc.SetBrush(*wxBLUE_BRUSH);
  dc.DrawRectangle(0, groundY, winWidth, winHeight);

  /* robot body */
  dc.SetBrush(*wxGREEN_BRUSH);
  dc.DrawPolygon(WXSIZEOF(points), points, 0, 0);

  /* robot arm */
  double armCos, armSin;
  std::tie(armCos, armSin) = GetCosAndSin(rotationAngle + _armAngle);
  int xArm = x4 + _armLength * armCos;
  int yArm = y4 - _armLength * armSin;

  dc.SetBrush(*wxYELLOW_BRUSH);
  dc.DrawLine(x4, y4, xArm, yArm);

  /* robot hand */
  double handCos, handSin;
  std::tie(handCos, handSin) = GetCosAndSin(_handAngle + rotationAngle);
  int xHand = xArm + _handLength * handCos;
  int yHand = yArm - _handLength * handSin;

  dc.SetBrush(*wxRED_BRUSH);
  dc.DrawLine(xArm, yArm, xHand, yHand);
}
