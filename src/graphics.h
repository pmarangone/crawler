#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <wx/dcclient.h>
#include <wx/listctrl.h>  // sizers 1 & 2
#include <wx/rawbmp.h>
#include <wx/timer.h>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class Graphics {
 public:
  // Default constructors
  Graphics();
  Graphics(wxWindow *parent, int width, int height);
  // Rule of five
  Graphics(const Graphics &) = delete;             // no-copying policy constructor (due to wxWidgets resource ownership)
  Graphics &operator=(const Graphics &) = delete;  // no-copying policy assigment operator constructor (due to wxWidgets ownership)
  Graphics(Graphics &&source);
  Graphics &operator=(Graphics &&source);
  // Destructor
  virtual ~Graphics();

  // Behavioral methods
  void DrawToBuffer();
  // Setters
  void SetTimerOwner(wxFrame *frame);
  void StartTimer(unsigned int t, bool oneShot);
  // Getters
  wxWindow *GetRenderSurface();
  wxBitmap *GetBitmapBuffer();
  // Behavioral methods
  void RebuildBufferAndRefresh();

 private:
  int _width;                 // bitmap width
  int _height;                // bitmap height
  wxBitmap _bitmapBuffer;     // pixels are drawn here
  wxWindow *_renderSurface;   // main graphics screen where things get rendered; gets moved to _sizerGraphics in the MainFrame
  unsigned char *_pixelData;  // 8 bit for rgba variable
  int _curRGB;                // temporary demo dependency
  wxTimer _timer;             // alternative to the while loop introduced by wxWidgets for consistent rendering
};

#endif /* GRAPHICS_H */

// How to embed SDl2 window into a wxWidgets panel: https://forums.wxwidgets.org/viewtopic.php?t=42189