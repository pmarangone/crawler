#ifndef GUI_H
#define GUI_H

#include <string>
#include <memory>

// For compilers that support precompilation, includes "wx/wx.h"; this global header already includes wx/wx.h
#include <wx/wxprec.h>
#include <wx/listctrl.h>  // sizers 1 & 2
// #include <wx/splitter.h>   // splitters

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "graphics.h"
#include "panel.h"


namespace GUI {
  const std::string appTitle{"Crawler CS188"};
  const int topPanelHeight{100};
  const int bottomPanelHeight{100};
  const int bitmapWidth{900};
  const int bitmapHeight{300};
  const int windowWidth{bitmapWidth};
  const int windowHeight{topPanelHeight + bitmapHeight + bottomPanelHeight};
  const wxPoint windowPosition{wxDefaultPosition};
  const wxSize windowSize{wxSize(windowWidth, windowHeight)};
  const long windowStyle{(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))};  // styles are responsible for a window's resize option
}  // namespace GUI


// Main frame; alternative – wxDialog
class MainFrame : public wxFrame {
 public:
  MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size, long style);  // https://docs.wxwidgets.org/stable/classwx_frame.html#a01b53ac2d4a5e6b0773ecbcf7b5f6af8
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
  // Update values
  void OnPlus(wxCommandEvent& event);
  void OnMinus(wxCommandEvent& event);

  wxStaticText *_learningRateText, *_discoutText, *_epsilonText;
  double _learningRate = 1, _discount = 1, _epsilon = 0.5;

  wxDECLARE_EVENT_TABLE();  // event table declaration for this particular class
  // Variables
  std::unique_ptr<Graphics> _graphics;
};


#endif /* GUI_H */


/*
For compilation problems (duplicate definitions), see https://www.howtobuildsoftware.com/index.php/how-do/bHE6/c-c-cuda-header-files-duplicate-symbol-duplicate-symbol-issue-with-c-headers 

*/