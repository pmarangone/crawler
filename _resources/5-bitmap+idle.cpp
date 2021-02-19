#include "wx/sizer.h"
#include "wx/wx.h"

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
  bool render_loop_on;
  bool OnInit();
  void onIdle(wxIdleEvent& evt);

  MyFrame* frame;
  BasicDrawPane* drawPane;

 public:
  void activateRenderLoop(bool on);
};

IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame {
 public:
  MyFrame() : wxFrame((wxFrame*)NULL, -1, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(400, 200)) {
  }
  void onClose(wxCloseEvent& evt) {
    wxGetApp().activateRenderLoop(false);
    evt.Skip();  // don't stop event, we still want window to close
  }
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_CLOSE(MyFrame::onClose)
END_EVENT_TABLE()

bool MyApp::OnInit() {
  render_loop_on = false;

  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new MyFrame();

  drawPane = new BasicDrawPane(frame);
  sizer->Add(drawPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->Show();

  activateRenderLoop(true);
  return true;
}

void MyApp::activateRenderLoop(bool on) {
  if (on && !render_loop_on) {
    Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyApp::onIdle));
    render_loop_on = true;
  } else if (!on && render_loop_on) {
    Disconnect(wxEVT_IDLE, wxIdleEventHandler(MyApp::onIdle));
    render_loop_on = false;
  }
}
void MyApp::onIdle(wxIdleEvent& evt) {
  if (render_loop_on) {
    drawPane->paintNow();
    evt.RequestMore();  // render continuously, not only once on idle
  }
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