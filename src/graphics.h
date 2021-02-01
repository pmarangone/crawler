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
  Graphics(wxWindow *parent, int width, int height);
  ~Graphics();
  void SetBackgroundStyle(wxBackgroundStyle style);
  void SetTimerOwner(wxFrame *frame);
  void StartTimer(unsigned int t);
  wxWindow *GetRenderSurface();
  wxBitmap *GetBitmapBuffer();
  void RebuildBufferAndRefresh();
 private:
  int _width;
  int _height;
  int _curRGB;
  wxTimer _timer;
  wxBitmap _bitmapBuffer;
  wxWindow *_renderSurface;
  unsigned char *_pixelData;  // 8 bit for rgba array
};

#endif /* GRAPHICS_H */

// How to embed SDl2 window into a wxWidgets panel: https://forums.wxwidgets.org/viewtopic.php?t=42189