// Intro to events
// Tutorial: https://www.youtube.com/watch?v=5v00F8hEV7E

// GUI.h

// https://docs.wxwidgets.org/3.0/overview_helloworld.html

// For compilers that support precompilation, includes "wx/wx.h"; this global header already includes wx/wx.h
#include <wx/wxprec.h>
#include <wx/listctrl.h>   // sizers 2
#include <wx/splitter.h>   // splitters

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

class MyApp : public wxApp {
 public:
  virtual bool OnInit();
};

// Main frame; alternative – wxDialog
class MyFrame : public wxFrame {
 public:
  MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
 private:
  // Event hanlers – no need to be virtual nor public
  void OnHello(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
	void OnClickBtn1(wxCommandEvent &event);	// btn1 mouse click handler
	void OnClickBtn2(wxCommandEvent &event);	// btn1 mouse click handler
	void OnClick(wxCommandEvent &event);	// mouse click handler
  wxDECLARE_EVENT_TABLE();  // event table declaration for this particular class
};

// Unique menu command identifiers
enum {
  ID_Hello = wxID_LAST + 1,
	ID_BTN1,
	ID_BTN2,
	ID_BTN3
  // No need to implement "About" and "Exit"
};

// Event table where events are routed to their respective handler functions in MyFrame class
// clang-format off
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(ID_Hello,   MyFrame::OnHello)
  EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
  EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
	EVT_BUTTON(ID_BTN1, MyFrame::OnClickBtn1)	// btn1 mouse click
	EVT_BUTTON(ID_BTN2, MyFrame::OnClickBtn2)	// btn2 mouse click
	EVT_BUTTON(wxID_ANY, MyFrame::OnClick)	// wxID_ANY here means we react the same way to all buttons; standard implementation should be in the bottom
wxEND_EVENT_TABLE()
; // clang-format on

// Custom panel class serving as a button's parent
class MyPanel : public wxPanel {
 public:
  MyPanel(wxWindow *parent); 
 private:
  void OnClick(wxCommandEvent &event);
  wxDECLARE_EVENT_TABLE();  // event table declaration for this particular class
};


// GUI.cpp

// Main function implementation
wxIMPLEMENT_APP(MyApp);

// Called upon startup and should be used to initialize the program
bool MyApp::OnInit() {
  MyFrame *frame = new MyFrame("Crawler CS188", (wxDefaultPosition), wxDefaultSize);
  frame->Show(true);
  return true;
}

// Main window constructor
MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
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


  wxButton *btn1 = new wxButton(this, ID_BTN1, "OK");	// ID number generated is negative
  wxButton *btn2 = new wxButton(this, ID_BTN2, "Click me!");
  wxButton *btn3 = new wxButton(this, ID_BTN3, "Click me!");

  wxBoxSizer *s1 = new wxBoxSizer(wxHORIZONTAL);
  s1->Add(btn1, 0, wxCENTER | wxALL, 50);
  s1->Add(btn2, 0, wxCENTER | wxALL, 50);
  s1->Add(btn3, 0, wxCENTER | wxALL, 50);

  this->SetSizerAndFit(s1);
}

// Event handlers
void MyFrame::OnExit(wxCommandEvent &event) {
  Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This application is built by Patrick Marangone and Sergei Kononov in an attempt to replicate the reinforcement learning crawler from UC Berkeley's CS188 class.", "About the Crawler", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage("Hello world from wxWidgets!");
}

// Mouse click for all btn
void MyFrame::OnClick(wxCommandEvent &event) {  // for events objects deriving from wxCommandEvent, the events get propagated thru parent controls (current parent where e.g. a button is, i.e. widnow, panel, frame, etc.) 
	std::cout << "Standard button clicked. ID: " << event.GetId() << std::endl;
  // event.Skip();  // force event propagation to the next EVT_BUTTON event in the table (omit, if you put EVT_BUTTON(wxID_ANY, MyFrame::OnClick) in the bottom of the event table)
}

void MyFrame::OnClickBtn1(wxCommandEvent &event) {
	std::cout << "Btn 1 clicked. ID: " << event.GetId() << std::endl;
}

void MyFrame::OnClickBtn2(wxCommandEvent &event) {
	std::cout << "Btn 2 clicked. ID: " << event.GetId() << std::endl;
}

// Custom panel class implementation
