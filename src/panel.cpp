#include "panel.h"


// Custom event table for the MyPanel class
// clang-format off
wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
  EVT_BUTTON(wxID_ANY, MyPanel::OnClick)  // standard event handler goes last (overriding)
wxEND_EVENT_TABLE()
; // clang-format on



// MyPanel constructor
MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent) {
  this->SetBackgroundColour(wxColour(200, 100, 100));
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
