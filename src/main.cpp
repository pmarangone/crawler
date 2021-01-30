// Intro to events
// Tutorial on events: https://www.youtube.com/watch?v=5v00F8hEV7E
// Tutorial on IDLE events: https://www.youtube.com/watch?v=4RkvSf6ExxY&list=PLpHIphr3laQbBLJ8j4iXy8lieaiY9Q10y&index=8

// GUI.h

// https://docs.wxwidgets.org/3.0/overview_helloworld.html

// For compilers that support precompilation, includes "wx/wx.h"; this global header already includes wx/wx.h
#include <wx/wxprec.h>
#include <wx/listctrl.h>   // sizers 2
// #include <wx/splitter.h>   // splitters

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

class CrawlerApp : public wxApp {
 public:
  virtual bool OnInit();
};

// Main frame; alternative – wxDialog
class AppFrame : public wxFrame {
 public:
  AppFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
 private:
  // Event hanlers – no need to be virtual nor public
  void OnHello(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  
	void OnClickBtn1(wxCommandEvent &event);	// btn1 mouse click handler
	void OnClickBtn2(wxCommandEvent &event);	// btn1 mouse click handler
	void OnClick(wxCommandEvent &);	// mouse click handler; event arg can be skipped
  void OnSize(wxSizeEvent &);
  void OnIdle(wxIdleEvent &);
  wxDECLARE_EVENT_TABLE();  // event table declaration for this particular class
};

// Custom panel class serving as a button's parent
class MyPanel : public wxPanel {
 public:
  void OnClickDynamic(wxCommandEvent &event);  // made public to be accessible from within AppFrame class (for demo)
  MyPanel(wxWindow *parent); 
 private:
  void OnClick(wxCommandEvent &event);
  void OnSize(wxSizeEvent &);  
  wxDECLARE_EVENT_TABLE();  // event table declaration for this particular class
};

// Unique menu command identifiers (regardless of the class)
enum {
  ID_Hello = wxID_LAST + 1,
	ID_BTN1,
	ID_BTN2,
	ID_BTN3
  // No need to implement "About" and "Exit"
};

// Custom vent table for AppFrame class where events are routed to their respective handler functions
// clang-format off
wxBEGIN_EVENT_TABLE(AppFrame, wxFrame)
  EVT_MENU(ID_Hello,   AppFrame::OnHello)
  EVT_MENU(wxID_EXIT,  AppFrame::OnExit)
  EVT_MENU(wxID_ABOUT, AppFrame::OnAbout)
	EVT_BUTTON(ID_BTN1, AppFrame::OnClickBtn1)	// btn1 mouse click
	EVT_BUTTON(ID_BTN2, AppFrame::OnClickBtn2)	// btn2 mouse click
	EVT_BUTTON(wxID_ANY, AppFrame::OnClick)	// wxID_ANY here means we react the same way to all buttons; standard implementation should be in the bottom
  EVT_SIZE(AppFrame::OnSize)
  EVT_IDLE(AppFrame::OnIdle)
wxEND_EVENT_TABLE()
; // clang-format on

// Custom event table for the MyPanel class
// clang-format off
wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
  EVT_BUTTON(wxID_ANY, MyPanel::OnClick)  // standard event handler goes last (overriding)
wxEND_EVENT_TABLE()
; // clang-format on



// GUI.cpp

// Main function implementation
wxIMPLEMENT_APP(CrawlerApp);

// Called upon startup and should be used to initialize the program
bool CrawlerApp::OnInit() {
  AppFrame *frame = new AppFrame("Crawler CS188", (wxDefaultPosition), wxDefaultSize);
  frame->Show(true);
  return true;
}

// Main window
AppFrame::AppFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
  // Setting menu items & status bar; list of standard IDs: https://docs.wxwidgets.org/3.0/page_stockitems.html
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
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

  // Buttons, sizer and panels

  wxButton *btn1 = new wxButton(this, ID_BTN1, "Button 1");	// ID number generated is negative
  wxButton *btn2 = new wxButton(this, ID_BTN2, "Button 2");
  wxButton *btn3 = new wxButton(this, ID_BTN3, "Standard Button");

  wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(btn1, 0, wxCENTER | wxALL, 25);
  sizer->Add(btn2, 0, wxCENTER | wxALL, 25);
  sizer->Add(btn3, 0, wxCENTER | wxALL, 25);

  MyPanel *panel = new MyPanel(this);
  wxButton *btn4 = new wxButton(panel, wxID_ANY, "Panel button");
  wxButton *btn5 = new wxButton(panel, wxID_ANY, "Dynamic event button");
  wxButton *btn6 = new wxButton(panel, wxID_ANY, "Dynamic lambda button");

  wxBoxSizer *panelSizer = new wxBoxSizer(wxHORIZONTAL);
  panelSizer->Add(btn4, 1, wxCENTER | wxALL, 25);
  panelSizer->Add(btn5, 1, wxCENTER | wxALL, 25);
  panelSizer->Add(btn6, 1, wxCENTER | wxALL, 25);
  panel->SetSizerAndFit(panelSizer);

  sizer->Add(panel, 1, wxEXPAND);
  this->SetSizerAndFit(sizer);

  // Dynamic event handling (no event table)
  btn5->Bind(wxEVT_BUTTON, &MyPanel::OnClickDynamic, panel);
  btn6->Bind(wxEVT_BUTTON, [](wxCommandEvent &event){
    std::cout << "PANEL dynamic LAMBDA button clicked. ID: " << event.GetId() << std::endl;
  });
}

// MyPanel constructor
MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent) {
  this->SetBackgroundColour(wxColour(200, 100, 100));
}

// Event handlers for AppFrame
void AppFrame::OnExit(wxCommandEvent &event) {
  Close(true);
}

void AppFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This application is built by Patrick Marangone and Sergei Kononov in an attempt to replicate the reinforcement learning crawler from UC Berkeley's CS188 class.", "About the Crawler", wxOK | wxICON_INFORMATION);
}

void AppFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage("Hello world from wxWidgets!");
}

// Mouse click for all btn
void AppFrame::OnClick(wxCommandEvent &event) {  // for events objects deriving from wxCommandEvent, the events get propagated thru parent controls (current parent where e.g. a button is, i.e. widnow, panel, frame, etc.) 
	std::cout << "Standard button clicked. ID: " << event.GetId() << std::endl;
  // event.Skip();  // force event propagation to the next EVT_BUTTON event in the table (omit, if you put EVT_BUTTON(wxID_ANY, AppFrame::OnClick) in the bottom of the event table)
}

void AppFrame::OnClickBtn1(wxCommandEvent &event) {
	std::cout << "Btn 1 clicked. ID: " << event.GetId() << std::endl;
}

void AppFrame::OnClickBtn2(wxCommandEvent &event) {
	std::cout << "Btn 2 clicked. ID: " << event.GetId() << std::endl;
}

void AppFrame::OnSize(wxSizeEvent &event) {
  std::cout << "FRAME size event; height: " << event.GetSize().GetHeight() << "; width: " << event.GetSize().GetWidth() << std::endl;
  event.Skip();  // Should call skip to not mess with the default implementation of size handlers (wxWidgets handles size events internally)
}

void AppFrame::OnIdle(wxIdleEvent &event) {
  // wxMessageBox("AppFrame::OnIdle");  // example of a popping dialog

}

// Event handlers for MyPanel
void MyPanel::OnClick(wxCommandEvent &event) {
  std::cout << "PANEL standard button clicked. ID: " << event.GetId() << std::endl;
  // event.Skip();  // if Skip() is called here, the event will propagate to the AppFrame class and will be handled by the standard mytton handler; works ONLY for wxCommandEvent, not for wxSizeEvent nor others
}

void MyPanel::OnClickDynamic(wxCommandEvent &event) {  // made public for demo
  std::cout << "PANEL dynamic button clicked. ID: " << event.GetId() << std::endl;
  // event.Skip();  // if Skip() is called here, the event will propagate to the AppFrame class and will be handled by the standard mytton handler; works ONLY for wxCommandEvent, not for wxSizeEvent nor others
}

void MyPanel::OnSize(wxSizeEvent &event) {
  std::cout << "PANEL size event; height: " << event.GetSize().GetHeight() << "; width: " << event.GetSize().GetWidth() << std::endl;
  event.Skip();  // even though the panel is the frame's child, the size event does not propagate to the frame
}