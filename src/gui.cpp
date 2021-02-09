#include "gui.h"

// Unique menu command identifiers (regardless of the class)
enum ID {  // No need to implement "About" and "Exit" (auto)
  Hello = wxID_LAST + 1,
  BTN_RUN,
  BTN_STOP
};

// Custom event table for MainFrame class where events are routed to their respective handler functions
// clang-format off
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
  EVT_MENU(ID::Hello, MainFrame::OnHello)
  EVT_MENU(wxID_EXIT, MainFrame::OnExit)
  EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
	EVT_BUTTON(ID::BTN_RUN, MainFrame::OnClickRun)	// run btn mouse click
	EVT_BUTTON(ID::BTN_STOP, MainFrame::OnClickStop)	// stop btn mouse click
	EVT_BUTTON(wxID_ANY, MainFrame::OnClick) // wxID_ANY here means we react the same way to all buttons; standard implementation should be in the bottom
  // EVT_SIZE(MainFrame::OnSize)
  // EVT_IDLE(MainFrame::OnIdle)
wxEND_EVENT_TABLE()
;  // clang-format on

// Main window

// Constructor for a non-resizable window (use wxDEFAULT_FRAME_STYLE style for a resizable window)
MainFrame::MainFrame(const wxString &title, const wxPoint &pos = GUI::windowPosition, const wxSize &size = GUI::windowSize, long style = GUI::windowStyle) 
                    : wxFrame(NULL, wxID_ANY, title, pos, size, style, title), _graphics(nullptr) {
  // Setting min & max size (to force no-resize option for Linux & Windows)
  // this->SetMinSize(GUI::windowSize);
  // this->SetMaxSize(GUI::windowSize);
  // Setting menu items & status bar; list of standard IDs: https://docs.wxwidgets.org/3.0/page_stockitems.html
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID::Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);
  // Including all menu items created into the menu bar
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");
  SetMenuBar(menuBar);
  // Status bar in the bottom of the main window
  CreateStatusBar();
  SetStatusText("Reinforcement Learning: Crawler CS188");

  // Contol panels
  wxPanel *panelTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::topPanelHeight));
  panelTop->SetBackgroundColour(wxColour(100, 200, 200));
  wxPanel *panelTopCH = new wxPanel(panelTop, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::topPanelHeight));
  // panelTopCH->SetBackgroundColour(wxColour(100, 200, 200));
  wxPanel *panelMiddle = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bitmapHeight));
  panelMiddle->SetBackgroundColour(wxColour(233, 233, 233));
  wxPanel *panelBottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bottomPanelHeight));
  panelBottom->SetBackgroundColour(wxColour(100, 100, 200));
  wxPanel *panelBottomCH = new wxPanel(panelBottom, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bottomPanelHeight));

  // Main vertical sizer
  wxBoxSizer *sizerMain = new wxBoxSizer(wxVERTICAL);
  sizerMain->Add(panelTop, 0, wxEXPAND);
  sizerMain->Add(panelMiddle, 1, wxEXPAND);
  sizerMain->Add(panelBottom, 0, wxEXPAND);

  // Top sizer (nested)
  wxSizer *sizerTopCV = new wxBoxSizer(wxVERTICAL);
  wxSizer *sizerTopCH = new wxBoxSizer(wxHORIZONTAL);

  // Three sizers for behavior controls
  wxSizer *sizerMotion = new wxBoxSizer(wxHORIZONTAL);
  wxSizer *sizerSteps = new wxBoxSizer(wxHORIZONTAL);
  wxSizer *sizerReset = new wxBoxSizer(wxHORIZONTAL);

  // sizerTopCH->Add(panelTopCH, 1, wxALIGN_CENTER);
  sizerMotion->Add(new wxButton(panelTop, ID::BTN_RUN, wxString::FromUTF8("Run \u25B6")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerMotion->Add(new wxButton(panelTop, ID::BTN_STOP, wxString::FromUTF8("Stop \u25FC")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  sizerSteps->Add(new wxButton(panelTop, wxID_ANY, "Skip 30K steps"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerSteps->Add(new wxButton(panelTop, wxID_ANY, "Skip 1000K steps"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  sizerReset->Add(new wxButton(panelTop, wxID_ANY, "Reset speed counter"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerReset->Add(new wxButton(panelTop, wxID_ANY, "Reset Q"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  sizerTopCH->Add(sizerMotion, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerTopCH->Add(sizerSteps, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerTopCH->Add(sizerReset, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  sizerTopCV->Add(sizerTopCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  panelTop->SetSizerAndFit(sizerTopCV);

  // Bottom sizer (nested)
  wxSizer *sizerBottomCV = new wxBoxSizer(wxVERTICAL);
  wxSizer *sizerBottomCH = new wxBoxSizer(wxHORIZONTAL);

  // Three sizers for grouped variable controls
  wxSizer *sizerEpsilon = new wxBoxSizer(wxHORIZONTAL);
  wxSizer *sizerGamma = new wxBoxSizer(wxHORIZONTAL);
  wxSizer *sizerAlpha = new wxBoxSizer(wxHORIZONTAL);

  sizerEpsilon->Add(new wxButton(panelBottom, wxID_ANY, wxString::FromUTF8("\u03B5++")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerEpsilon->Add(new wxButton(panelBottom, wxID_ANY, wxString::FromUTF8("\u03B5--")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  sizerGamma->Add(new wxButton(panelBottom, wxID_ANY,  wxString::FromUTF8("\u03B3++")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerGamma->Add(new wxButton(panelBottom, wxID_ANY,  wxString::FromUTF8("\u03B3--")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  sizerAlpha->Add(new wxButton(panelBottom, wxID_ANY, wxString::FromUTF8("\u03B1++")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  sizerAlpha->Add(new wxButton(panelBottom, wxID_ANY, wxString::FromUTF8("\u03B1--")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  sizerBottomCH->Add(sizerEpsilon, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 15);
  sizerBottomCH->Add(sizerGamma, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 15);
  sizerBottomCH->Add(sizerAlpha, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 15);

  sizerBottomCV->Add(sizerBottomCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  panelBottom->SetSizerAndFit(sizerBottomCV);

  // Middle sizer – _graphics
  _graphics = std::make_unique<Graphics>(panelMiddle, GUI::bitmapWidth, GUI::bitmapHeight);
  _graphics->SetBackgroundStyle(wxBG_STYLE_PAINT);
  _graphics->GetRenderSurface()->Bind(wxEVT_PAINT, &MainFrame::OnPaint, this);  // impl in parent though handle

  wxBoxSizer* sizerGraphics = new wxBoxSizer(wxVERTICAL);
  sizerGraphics->Add(_graphics->GetRenderSurface(), 1, wxALIGN_CENTER);
  panelMiddle->SetSizerAndFit(sizerGraphics);
  // Layout(); // resize element to cover the entire window: https://docs.wxwidgets.org/trunk/classwx_top_level_window.html#adfe7e3f4a32f3ed178968f64431bbfe0

  _graphics->SetTimerOwner(this);
  _graphics->StartTimer(17);
  this->Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);

  this->SetSizerAndFit(sizerMain);
}

MainFrame::~MainFrame() {}

// Event handlers for MainFrame
void MainFrame::OnExit(wxCommandEvent &event) {
  Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This application is built by Patrick Marangone and Sergei Kononov in an attempt to replicate the reinforcement learning crawler from UC Berkeley CS188 class.", "About the Crawler", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage("Hello world from wxWidgets!");
}

void MainFrame::OnClickRun(wxCommandEvent &event) {
  std::cout << "RUN btn clicked. ID: " << event.GetId() << std::endl;
}

void MainFrame::OnClickStop(wxCommandEvent &event) {
  std::cout << "STOP btn clicked. ID: " << event.GetId() << std::endl;
}

// Mouse click for all btn
void MainFrame::OnClick(wxCommandEvent &event) {  // for events objects deriving from wxCommandEvent, the events get propagated thru parent controls (current parent where e.g. a button is, i.e. widnow, panel, frame, etc.)
  std::cout << "Standard button clicked. ID: " << event.GetId() << std::endl;
  // event.Skip();  // force event propagation to the next EVT_BUTTON event in the table (omit, if you put EVT_BUTTON(wxID_ANY, MainFrame::OnClick) in the bottom of the event table)
}

// void MainFrame::OnSize(wxSizeEvent &event) {
//   std::cout << "FRAME size event; height: " << event.GetSize().GetHeight() << "; width: " << event.GetSize().GetWidth() << std::endl;
//   event.Skip();  // Should call skip to not mess with the default implementation of size handlers (wxWidgets handles size events internally)
// }

// void MainFrame::OnIdle(wxIdleEvent &event) {
//   // wxMessageBox("MainFrame::OnIdle");  // example of a popping dialog
//   std::cout << "On idle event" << std::endl;
// }

void MainFrame::OnPaint(wxPaintEvent& event) {
  wxPaintDC dc(_graphics->GetRenderSurface());  // TODO(SK): take a deeper look into rendering mechanism (Reminder for SK) 
  if (_graphics->GetBitmapBuffer()->IsOk()) {
    dc.DrawBitmap(*_graphics->GetBitmapBuffer(), 0, 0);
  }
}

void MainFrame::OnTimer(wxTimerEvent& event) {
  _graphics->RebuildBufferAndRefresh();
}
