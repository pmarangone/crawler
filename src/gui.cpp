#include "gui.h"

// wxWidgets entry point: hands over control of main to wxWidgets
// Called upon wxWidgets startup and should be used to initialize the program
bool CrawlerApp::OnInit() {
  MainFrame *frame = new MainFrame("Crawler CS188", (wxDefaultPosition), wxDefaultSize);
  frame->Show(true);
  return true;
}

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
MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
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
  wxPanel *panelTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 100));
  panelTop->SetBackgroundColour(wxColour(100, 200, 200));
  wxPanel *panelTopCH = new wxPanel(panelTop, wxID_ANY, wxDefaultPosition, wxSize(400, 100));
  // panelTopCH->SetBackgroundColour(wxColour(100, 200, 200));
  wxPanel *panelMiddle = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 100));
  panelMiddle->SetBackgroundColour(wxColour(233, 233, 233));
  wxPanel *panelBottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 100));
  panelBottom->SetBackgroundColour(wxColour(100, 100, 200));
  wxPanel *panelBottomCH = new wxPanel(panelBottom, wxID_ANY, wxDefaultPosition, wxSize(400, 100));

  // Main vertical sizer
  wxBoxSizer *sizerMain = new wxBoxSizer(wxVERTICAL);
  sizerMain->Add(panelTop, 0, wxEXPAND);
  sizerMain->Add(panelMiddle, 1, wxEXPAND);
  sizerMain->Add(panelBottom, 0, wxEXPAND);

  // Top sizer (nested)
  wxSizer *sizerTopCV = new wxBoxSizer(wxVERTICAL);
  wxSizer *sizerTopCH = new wxBoxSizer(wxHORIZONTAL);

  // sizerTopCH->Add(panelTopCH, 1, wxALIGN_CENTER);
  sizerTopCH->Add(new wxButton(panelTop, ID::BTN_RUN, "Run"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 15);
  sizerTopCH->Add(new wxButton(panelTop, ID::BTN_STOP, "Stop"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 15);
  sizerTopCV->Add(sizerTopCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  panelTop->SetSizerAndFit(sizerTopCV);

  // Bottom sizer (nested)
  wxSizer *sizerBottomCV = new wxBoxSizer(wxVERTICAL);
  wxSizer *sizerBottomCH = new wxBoxSizer(wxHORIZONTAL);

  sizerBottomCH->Add(new wxButton(panelBottom, wxID_ANY, "Button 1"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 15);
  sizerBottomCH->Add(new wxButton(panelBottom, wxID_ANY, "Button 2"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 15);
  sizerBottomCV->Add(sizerBottomCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  panelBottom->SetSizerAndFit(sizerBottomCV);

  this->SetSizerAndFit(sizerMain);

  //   // SDL window
  //   SDL_Window *sdlWindow = SDL_CreateWindowFrom((void *) panelMiddle->GetHandle());
  //   if (sdlWindow == NULL) {
  //     std::cerr << "SDL NULL Pointer ERROR";
  //     return;
  //   }
  //   SDL_Surface *windowSurface = nullptr;
  //  // This line causes a segmentation fault
  //   windowSurface = SDL_GetWindowSurface(sdlWindow);
}

// Event handlers for MainFrame
void MainFrame::OnExit(wxCommandEvent &event) {
  Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This application is built by Patrick Marangone and Sergei Kononov in an attempt to replicate the reinforcement learning crawler from UC Berkeley's CS188 class.", "About the Crawler", wxOK | wxICON_INFORMATION);
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