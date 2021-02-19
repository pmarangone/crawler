#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/wx.h>

class BasicDrawPane;

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
  MyFrame() : wxFrame((wxFrame*)NULL, -1, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(400, 200)) {
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

void BasicDrawPane::render(wxDC& dc) {
  static int y = 0;
  static int y_speed = 2;

  y += y_speed;
  if (y < 0) y_speed = 2;
  if (y > 200) y_speed = -2;

  dc.SetBackground(*wxWHITE_BRUSH);
  dc.Clear();
  dc.DrawText(wxT("Testing"), 40, y);
}