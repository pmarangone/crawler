#ifndef PANEL_H
#define PANEL_H

// For compilers that support precompilation, includes "wx/wx.h"; this global header already includes wx/wx.h
#include <wx/wxprec.h>
#include <wx/listctrl.h>   // sizers 2
// #include <wx/splitter.h>   // splitters

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

// Custom panel class serving as a button's parent
class ControlPanel : public wxPanel {
 public:
  ControlPanel(wxWindow *parent); 
  ControlPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name); 
  void OnClickDynamic(wxCommandEvent &event);  // made public to be accessible from within MainFrame class (for demo)
 private:
  void OnClick(wxCommandEvent &event);
  void OnSize(wxSizeEvent &);  
  wxDECLARE_EVENT_TABLE();  // event table declaration for this particular class
};


#endif /* PANEL_H */