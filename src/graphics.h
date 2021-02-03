#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <wx/wxprec.h>
#include <wx/listctrl.h>  // sizers 1 & 2
#include <wx/dcclient.h>
#include <wx/rawbmp.h>
#include <wx/timer.h>

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

class Graphics {
 public:
  // Default constructors
  Graphics();
  Graphics(wxWindow *parent, int width, int height);
  // Rule of five
  Graphics(const Graphics &) = delete;  // no-copying policy constructor (due to wxWidgets resource ownership)
  Graphics &operator=(const Graphics &) = delete;  // no-copying policy assigment operator constructor (due to wxWidgets ownership)
  Graphics(Graphics &&source);
  Graphics &operator=(Graphics &&course);
  virtual ~Graphics();  // virtual destructor
  // Setters and getters
  void SetBackgroundStyle(wxBackgroundStyle style);
  void SetTimerOwner(wxFrame *frame);
  void StartTimer(unsigned int t);
  wxWindow *GetRenderSurface();
  wxBitmap *GetBitmapBuffer();
  // Behavioral methods
  void RebuildBufferAndRefresh();
 private:
  int _width;
  int _height;
  int _curRGB;
  wxTimer _timer;
  wxBitmap _bitmapBuffer;
  wxWindow *_renderSurface;
  unsigned char *_pixelData;  // 8 bit for rgba variable
};

#endif /* GRAPHICS_H */

// How to embed SDl2 window into a wxWidgets panel: https://forums.wxwidgets.org/viewtopic.php?t=42189