#include "panel.h"


// Custom event table for the ControlPanel class
// clang-format off
wxBEGIN_EVENT_TABLE(ControlPanel, wxPanel)
  EVT_BUTTON(wxID_ANY, ControlPanel::OnClick)  // standard event handler goes last (overriding)
wxEND_EVENT_TABLE()
; // clang-format on



// ControlPanel constructor
ControlPanel::ControlPanel(wxWindow *parent) : wxPanel(parent) {
  this->SetBackgroundColour(wxColour(200, 100, 100));
}

// Constructor inheritance
ControlPanel::ControlPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name) : wxPanel(parent, id, pos, size, style, name) {}

// Event handlers for ControlPanel
void ControlPanel::OnClick(wxCommandEvent &event) {
  std::cout << "PANEL standard button clicked. ID: " << event.GetId() << std::endl;
  // event.Skip();  // if Skip() is called here, the event will propagate to the MainFrame class and will be handled by the standard mytton handler; works ONLY for wxCommandEvent, not for wxSizeEvent nor others
}

void ControlPanel::OnClickDynamic(wxCommandEvent &event) {  // made public for demo
  std::cout << "PANEL dynamic button clicked. ID: " << event.GetId() << std::endl;
  // event.Skip();  // if Skip() is called here, the event will propagate to the MainFrame class and will be handled by the standard mytton handler; works ONLY for wxCommandEvent, not for wxSizeEvent nor others
}

void ControlPanel::OnSize(wxSizeEvent &event) {
  std::cout << "PANEL size event; height: " << event.GetSize().GetHeight() << "; width: " << event.GetSize().GetWidth() << std::endl;
  event.Skip();  // even though the panel is the frame's child, the size event does not propagate to the frame
}
