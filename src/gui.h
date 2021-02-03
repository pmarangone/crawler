#ifndef GUI_H
#define GUI_H

// For compilers that support precompilation, includes "wx/wx.h"; this global header already includes wx/wx.h
#include <wx/wxprec.h>
#include <wx/listctrl.h>  // sizers 1 & 2
// #include <wx/splitter.h>   // splitters

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "graphics.h"
#include "panel.h"

class CrawlerApp : public wxApp {
 public:
  virtual bool OnInit();  // wxWidgets entry point: hands over control of main to wxWidgets
};

// Main frame; alternative – wxDialog
class MainFrame : public wxFrame {
 public:
  MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
  virtual ~MainFrame();
 private:
  // Event handlers – no need to be virtual nor public
  // Menu
  void OnHello(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  // Buttons
	void OnClickRun(wxCommandEvent &event);
	void OnClickStop(wxCommandEvent &event);
	void OnClick(wxCommandEvent &);	// mouse click handler; event arg can be skipped
  // Graphics
  void OnPaint(wxPaintEvent &event);
  void OnTimer(wxTimerEvent &event);
  // Misc
  void OnSize(wxSizeEvent &);
  // void OnIdle(wxIdleEvent &);
  wxDECLARE_EVENT_TABLE();  // event table declaration for this particular class
  // Variables
  int _width;
  Graphics _graphics;
};


#endif /* GUI_H */


/*
For compilation problems (duplicate definitions), see https://www.howtobuildsoftware.com/index.php/how-do/bHE6/c-c-cuda-header-files-duplicate-symbol-duplicate-symbol-issue-with-c-headers 

*/