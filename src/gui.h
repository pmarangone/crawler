#ifndef GUI_H
#define GUI_H

#include <wx/listctrl.h>  // wxSizer
#include <wx/spinctrl.h>  // wxSpinCtrlDouble
#include <wx/statbox.h>   // wxStaticBox
#include <wx/wxprec.h>

#include <iostream>
#include <memory>
#include <string>

// For compilers that support precompilation, includes "wx/wx.h"; this global header already includes wx/wx.h
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "crawlingRobot.h"
#include "graphics.h"

// clang-format off
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
  const long windowStyleNonResizable{(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))};  // styles are responsible for a window's resize option
  const long windowStyleResizable{wxDEFAULT_FRAME_STYLE};
  const wxColour topPanelBgrColor{wxColour(100, 200, 200)};
  const wxColour middlePanelBgrColor{wxColour(233, 233, 233)};
  const wxColour bottomPanelBgrColor{wxColour(100, 100, 200)};
}  // namespace GUI
;  // clang-format on

// Event & command IDs
enum ID {  // No need to implement "About" and "Exit" (automatic)
  MENU_HELLO = wxID_LAST + 1,
  BTN_RUN,
  BTN_STOP,
  SPIN_LEARNINGRATE,
  SPIN_STEPDELAY,
  SPIN_DISCOUNT,
  SPIN_EPSILON
};

// Main frame; alternative – wxDialog
class MainFrame : public wxFrame {
 public:
  MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size, long style);
  virtual ~MainFrame();

 private:
  // GUI initializers
  void InitMenu();
  void InitPanelTop();
  void InitPanelBottom();
  void InitPanelGraphics();
  void InitGraphics(wxPanel *parent);
  void InitAppLayout();  // fits all panels and their nested sizers into the main sizer in the main frame
  // Behavioral methods
  void LaunchRendererer();
  // Event handlers – no need to be virtual nor public
  // Menu
  void OnHello(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  // Buttons
  void OnClickRun(wxCommandEvent &event);
  void OnClickStop(wxCommandEvent &event);
  void OnClick(wxCommandEvent &event);
  // Spin controls
  void OnSpinCtrl(wxSpinDoubleEvent &event);  // handles all controls

  // Private variables
  // Crawling robot
  std::unique_ptr<CrawlingRobot> _robot;
  // Graphics
  std::unique_ptr<Graphics> _graphics;
  // GUI parts (in case there is a need for dynamic GUI)
  // Menu
  wxMenuBar *_menuBar{nullptr};
  wxMenu *_menuFile{nullptr};
  wxMenu *_menuHelp{nullptr};
  // Panels
  wxPanel *_panelTop{nullptr};
  wxPanel *_panelTopCH{nullptr};  // CH = centered horizontally
  wxPanel *_panelGraphics{nullptr};
  wxPanel *_panelBottom{nullptr};
  wxPanel *_panelBottomCH{nullptr};  // CH = centered horizontally
  // Main sizer
  wxBoxSizer *_sizerMain{nullptr};
  // Top panel sizers
  wxSizer *_sizerTopCV{nullptr};
  wxSizer *_sizerTopCH{nullptr};
  // Control button sizers (top panel)
  wxSizer *_sizerMotion{nullptr};
  wxSizer *_sizerSteps{nullptr};
  wxSizer *_sizerReset{nullptr};
  // Graphics sizer (middle panel)
  wxBoxSizer *_sizerGraphics{nullptr};
  // Bottom panel sizers
  wxSizer *_sizerBottomCV{nullptr};
  wxSizer *_sizerBottomCH{nullptr};
  // Spin control variable sizers (bottom panel)
  wxSizer *_sizerStepDelay{nullptr};
  wxSizer *_sizerEpsilon{nullptr};
  wxSizer *_sizerDiscount{nullptr};
  wxSizer *_sizerLearningRate{nullptr};
  // Spin controls (bottom panel)
  wxSpinCtrlDouble *_ctrlLearningRate{nullptr};
  wxSpinCtrlDouble *_ctrlStepDelay{nullptr};
  wxSpinCtrlDouble *_ctrlDiscount{nullptr};
  wxSpinCtrlDouble *_ctrlEpsilon{nullptr};
  // Event table declaration for the MainFrame class
  wxDECLARE_EVENT_TABLE();
};

#endif /* GUI_H */

// For compilation problems (duplicate definitions), see https://www.howtobuildsoftware.com/index.php/how-do/bHE6/c-c-cuda-header-files-duplicate-symbol-duplicate-symbol-issue-with-c-headers