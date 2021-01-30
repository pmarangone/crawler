#ifndef GUI_H
#define GUI_H

// For compilers that support precompilation, includes "wx/wx.h"; this global header already includes wx/wx.h
#include <wx/wxprec.h>
#include <wx/listctrl.h>   // sizers 2
// #include <wx/splitter.h>   // splitters

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "panel.h"

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


#endif /* GUI_H */


/*
For compilation problems (duplicate definitions), see https://www.howtobuildsoftware.com/index.php/how-do/bHE6/c-c-cuda-header-files-duplicate-symbol-duplicate-symbol-issue-with-c-headers 

*/