#include "gui.h"

// Main function implementation
wxIMPLEMENT_APP(CrawlerApp);

// Called upon startup and should be used to initialize the program
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
; // clang-format on


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
  panelTop->SetBackgroundColour(wxColour(229, 255, 204));
  wxPanel *panelTopCH = new wxPanel(panelTop, wxID_ANY, wxDefaultPosition, wxSize(400, 100));
  panelTopCH->SetBackgroundColour(wxColour(100, 200, 200));
  wxPanel *panelBottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 100));
  panelBottom->SetBackgroundColour(wxColour(100, 100, 200));
  
  // Main vertical sizer
  wxBoxSizer *sizerMain = new wxBoxSizer(wxVERTICAL);
  sizerMain->Add(panelTop, 0, wxEXPAND);
  sizerMain->Add(panelBottom, 1, wxEXPAND);

  // Nested centered sizer
  wxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
  wxSizer *sizerTopCH = new wxBoxSizer(wxHORIZONTAL);
  sizerTopCH->Add(panelTopCH, 0, wxALIGN_CENTER);
  sizerTop->Add(sizerTopCH, 1, wxALIGN_CENTER);

  this->SetSizerAndFit(sizerMain);


  // // Nested sizer; children are handled separately from parents
  // wxSizer *sizer_bottom = new wxBoxSizer(wxVERTICAL);
  // wxSizer *sizer_centered = new wxBoxSizer(wxHORIZONTAL);
  // sizer_centered->Add(panel_bottom_right, 0, wxALIGN_CENTER);
  // sizer_bottom->Add(sizer_centered, 1, wxALIGN_CENTER);
  
  // panel_bottom->SetSizerAndFit(sizer_bottom);

  // this->SetSizerAndFit(sizer);



  // wxButton *btnRun = new wxButton(panelCentered, ID::BTN_RUN, "Run");
  // wxButton *btnStop = new wxButton(panelCentered, ID::BTN_STOP, "Stop");
  
  // wxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
  // wxSizer *sizerTopCentered = new wxBoxSizer(wxHORIZONTAL);
  // // sizerTopCentered->Add(btnRun, 0, wxCENTER | wxLEFT | wxRIGHT, 10);
  // // sizerTopCentered->Add(btnStop, 0, wxCENTER | wxLEFT | wxRIGHT, 10);
  // sizerTopCentered->Add(panelCentered, 0, wxALIGN_CENTER);
  // sizerTop->Add(sizerTopCentered, 1, wxALIGN_CENTER);
  // panelTop->SetSizerAndFit(sizerTop);


  





  // wxBoxSizer *sizerPanelTop = new wxBoxSizer(wxHORIZONTAL);
  // sizerPanelTop->Add(sizerTopCentered, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 25);
  
  // panelTop->SetSizerAndFit(sizerPanelTop);

  // Contol panel bottom
  // ...

  // Graphics window
  // ...

  // Merge everything into the main frame
  // sizerMain->Add(panelTop, 0, wxEXPAND);
  // sizerMain->Add(panelBottom, 1, wxEXPAND);
  // this->SetSizerAndFit(sizerMain);

  // Tutorial
  // Custom wxPanels
  // wxPanel *panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));  // reference: https://docs.wxwidgets.org/trunk/classwx_panel.html;  1st arg is a parent; this = main frame pointer; can use wxDefaultSize instead of fixed size;
  // panel_top->SetBackgroundColour(wxColour(100, 100, 200));  // purple
  // wxPanel *panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
  // panel_bottom->SetBackgroundColour(wxColour(100, 200, 100));  // green
  // wxPanel *panel_bottom_right = new wxPanel(panel_bottom, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
  // panel_bottom_right->SetBackgroundColour(wxColour(200, 200, 100));  // brown
  // // Sizers to dynamically control window's position and size; wxBoxSizer::Add reference: https://forums.wxwidgets.org/viewtopic.php?t=14339, https://docs.wxwidgets.org/trunk/classwx_sizer.html, **https://docs.wxwidgets.org/trunk/classwx_sizer.html#aedfc0bfd98114c348766431dcb49c9f3
  
  // // Top/main box panel (control)
  // wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);  // when more objects added to the sizer, they will be stacked vertically
  // sizer->Add(panel_top, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);  // 2nd arg means how much space the control takes in its parent; 0 means the panel stays of the same size no matter how large the parent becomes, x > 0 determines how much space the contol takes relative to the same controls in the same sizer (1 = full stretch); 3rd arg wxEXPAND means the sizer expands horizontally on resize; | "wxALL, 5" sets margin of 5px on all 4 sides og the control
  // sizer->Add(panel_bottom, 1, wxEXPAND | wxALL, 10);
  
  // // Nested sizer; children are handled separately from parents
  // wxSizer *sizer_bottom = new wxBoxSizer(wxVERTICAL);
  // wxSizer *sizer_centered = new wxBoxSizer(wxHORIZONTAL);
  // sizer_centered->Add(panel_bottom_right, 0, wxALIGN_CENTER);
  // sizer_bottom->Add(sizer_centered, 1, wxALIGN_CENTER);
  
  // panel_bottom->SetSizerAndFit(sizer_bottom);

  // this->SetSizerAndFit(sizer);
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