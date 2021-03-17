#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <wx/dcclient.h>
#include <wx/listctrl.h>  // sizers 1 & 2
#include <wx/rawbmp.h>
#include <wx/timer.h>
#include <wx/wxprec.h>

#include <cassert>
#include <memory>
#include <tuple>

#include "robot.h"
#include "robotEnv.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class RenderTimer;

class Graphics : public wxWindow {
 public:
  // Default constructors
  Graphics();
  Graphics(wxPanel *parent, std::shared_ptr<Robot> &robot, int width, int height);
  // Rule of five
  Graphics(const Graphics &) = delete;             // no-copying policy constructor (due to wxWidgets resource ownership)
  Graphics &operator=(const Graphics &) = delete;  // no-copying policy assigment operator constructor (due to wxWidgets ownership)
  Graphics(Graphics &&source);
  Graphics &operator=(Graphics &&source);
  // Destructor
  virtual ~Graphics();
  // Setters
  void SetTimerOwner(wxFrame *frame);
  // Behavioral methods
  void InitLoop();
  void InitLoop(unsigned int t, bool isOneShot);
  void Render(wxDC &dc);
  void paintEvent(wxPaintEvent &event);
  void paintNow();
  void Notify();

 private:
  int _width;      // bitmap width
  int _height;     // bitmap height
  wxTimer _timer;  // alternative to the while loop introduced by wxWidgets for consistent rendering

  // Crawling robot
  std::shared_ptr<Robot> _robot{nullptr};

  DECLARE_EVENT_TABLE()
};

#endif /* GRAPHICS_H */