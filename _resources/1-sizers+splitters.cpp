// Tutorial: https://www.youtube.com/watch?v=kPB5Y6ef9dw
// Basic structure https://docs.wxwidgets.org/3.0/overview_helloworld.html

// To test sizers and splitters, see "Sizers 1", "Sizers 2" and "Splitters", uncomment, run and play with window sizes.

// GUI.h

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
  wxDECLARE_EVENT_TABLE();
};

// Unique menu command identifiers
enum {
  ID_Hello = 1
  // No need to implement "About" and "Exit"
};

// Event table where events are routed to their respective handler functions in MyFrame class
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(ID_Hello,   MyFrame::OnHello)
  EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
  EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

// GUI.cpp

// Main function implementation
wxIMPLEMENT_APP(MyApp);

// Called upon startup and should be used to initialize the program
bool MyApp::OnInit() {
  MyFrame *frame = new MyFrame("Crawler CS188", wxPoint(50, 50), wxSize(800, 600));
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

  /*  Sizers 1: Experimenting with window, panels and sizers

  // Custom wxPanels
  wxPanel *panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));  // reference: https://docs.wxwidgets.org/trunk/classwx_panel.html;  1st arg is a parent; this = main frame pointer; can use wxDefaultSize instead of fixed size;
  panel_top->SetBackgroundColour(wxColour(100, 100, 200));  // purple
  wxPanel *panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
  panel_bottom->SetBackgroundColour(wxColour(100, 200, 100));  // green
  wxPanel *panel_bottom_right = new wxPanel(panel_bottom, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
  panel_bottom_right->SetBackgroundColour(wxColour(200, 200, 100));  // brown
  // Sizers to dynamically control window's position and size; wxBoxSizer::Add reference: https://forums.wxwidgets.org/viewtopic.php?t=14339, https://docs.wxwidgets.org/trunk/classwx_sizer.html, **https://docs.wxwidgets.org/trunk/classwx_sizer.html#aedfc0bfd98114c348766431dcb49c9f3
  
  // Top/main box panel (control)
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);  // when more objects added to the sizer, they will be stacked vertically
  sizer->Add(panel_top, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);  // 2nd arg means how much space the control takes in its parent; 0 means the panel stays of the same size no matter how large the parent becomes, x > 0 determines how much space the contol takes relative to the same controls in the same sizer (1 = full stretch); 3rd arg wxEXPAND means the sizer expands horizontally on resize; | "wxALL, 5" sets margin of 5px on all 4 sides og the control
  sizer->Add(panel_bottom, 1, wxEXPAND | wxALL, 10);
  
  // Nested sizer; children are handled separately from parents
  wxSizer *sizer_bottom = new wxBoxSizer(wxVERTICAL);
  wxSizer *sizer_centered = new wxBoxSizer(wxHORIZONTAL);
  sizer_centered->Add(panel_bottom_right, 0, wxALIGN_CENTER);
  sizer_bottom->Add(sizer_centered, 1, wxALIGN_CENTER);
  
  panel_bottom->SetSizerAndFit(sizer_bottom);

  this->SetSizerAndFit(sizer);
  */


  /* Sizers 2: columns, items and buttons 
  wxListView *list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
  list->InsertColumn(0, "Name");
  list->InsertItem(0, "Item");

  wxButton *ok_button = new wxButton(this, wxID_ANY, "OK");
  wxButton *cancel_button = new wxButton(this, wxID_ANY, "Cancel");

  wxBoxSizer *s1 = new wxBoxSizer(wxVERTICAL);
  s1->Add(list, 1, wxEXPAND | wxALL, 5);
  
  wxBoxSizer *s2 = new wxBoxSizer(wxHORIZONTAL);
  s2->Add(ok_button, 0, wxRIGHT, 5);
  s2->Add(cancel_button, 0);

  s1->Add(s2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5);

  this->SetSizerAndFit(s1);
  */

  /* Splitters */
  wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

  wxSplitterWindow *right_splitter = new wxSplitterWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

  wxPanel *left = new wxPanel(splitter);  // splitter added as a parent; splitters are controls, raise from wxFrame –> different with sizers
  wxPanel *right = new wxPanel(right_splitter);
  wxPanel *bottom = new wxPanel(right_splitter);

  left->SetBackgroundColour(wxColour(200, 100, 100));
  right->SetBackgroundColour(wxColour(100, 200, 100));
  bottom->SetBackgroundColour(wxColour(200, 200, 100));

  right_splitter->SetMinimumPaneSize(100);
  right_splitter->SplitHorizontally(right, bottom);

  right_splitter->SetSashGravity(1.0);  // decides which panel changes size and which stays static on resize; 1.0 makes top/left (v/h) splitter resize; 0.5 makes the panels equal; 0 makes the bottom/right panel automatically resize

  splitter->SetMinimumPaneSize(200);
  splitter->SplitVertically(left, right_splitter);
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