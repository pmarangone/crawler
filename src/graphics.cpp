#include "graphics.h"

Graphics::Graphics(wxWindow* parent,
                   int width, int height) : _width(width),
                                            _height(height),
                                            _pixelData(new unsigned char [3 * _width * _height]),
                                            _renderSurface(new wxWindow(parent, wxID_ANY, wxDefaultPosition,
                                                                        wxSize(width, height))) {
  _curRGB = 0;
}

Graphics::~Graphics() {
  delete [] _pixelData;
  _timer.Stop();
}

void Graphics::SetBackgroundStyle(wxBackgroundStyle style) {
  this->_renderSurface->SetBackgroundStyle(style);
};

wxWindow *Graphics::GetRenderSurface() {
  return this->_renderSurface;
}

wxBitmap *Graphics::GetBitmapBuffer() {
  return &(this->_bitmapBuffer);
}

void Graphics::SetTimerOwner(wxFrame *frame) {
  this->_timer.SetOwner(frame);
};

void Graphics::StartTimer(unsigned int t) {
  this->_timer.Start(t);
};

void Graphics::RebuildBufferAndRefresh() {
  // Build the pixel buffer here, for this simple example just set all pixels to the same value and then increment that value.
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      _pixelData[3 * y * _width + 3 * x] = _curRGB;
      _pixelData[3 * y * _width + 3 * x + 1] = _curRGB;
      _pixelData[3 * y * _width + 3 * x + 2] = _curRGB;
    }
  }

  ++_curRGB;
  if (_curRGB > 255) {
    _curRGB = 0;
  }

  // Now transfer the pixel data into a wxBitmap
  wxBitmap b(_width, _height, 24);
  wxNativePixelData data(b);

  if (!data) {
    // ... raw access to bitmap data unavailable, do something else ...
    return;
  }

  wxNativePixelData::Iterator p(data);

  int curPixelDataLoc = 0;
  for (int y = 0; y < _height; ++y) {
    wxNativePixelData::Iterator rowStart = p;
    for (int x = 0; x < _width; ++x, ++p) {
      p.Red() = _pixelData[curPixelDataLoc++];
      p.Green() = _pixelData[curPixelDataLoc++];
      p.Blue() = _pixelData[curPixelDataLoc++];
    }
    p = rowStart;
    p.OffsetY(data, 1);
  }

  _bitmapBuffer = b;
  _renderSurface->Refresh();
  _renderSurface->Update();
}