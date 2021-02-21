#include "graphics.h"

// Default constructor
Graphics::Graphics() : _width(1),
                       _height(1),
                       _curRGB(0),
                       _bitmapBuffer(_width, _height, 24),
                       _renderSurface(nullptr),
                       _pixelData(nullptr) {}

// Overloaded default constructor
Graphics::Graphics(wxWindow *parent, int width, int height)
    : _width(width),
      _height(height),
      _curRGB(0),
      _pixelData(new unsigned char[3 * _width * _height]),
      _renderSurface(new wxWindow(parent,
                                  wxID_ANY,
                                  wxDefaultPosition,
                                  wxSize(width, height))) {
  _renderSurface->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

// Move constructor
Graphics::Graphics(Graphics &&source) {
  // Point variables / assign values
  _pixelData = source._pixelData;
  _renderSurface = source._renderSurface;
  _bitmapBuffer = std::move(source._bitmapBuffer);  // source invalidated by moving
  _width = source._width;
  _height = source._height;
  _curRGB = source._curRGB;
  // _timer left out (no copying policy imposed by wxWidgets)
  // Invalidate source
  source._pixelData = nullptr;
  source._renderSurface = nullptr;
  source._width = 0;
  source._height = 0;
  source._curRGB = 0;
  std::cout << "Moved instance " << &source << " to " << this << std::endl;
}

// Move assignment operator constructor
Graphics &Graphics::operator=(Graphics &&source) {
  if (this == &source) {
    return *this;
  }
  // Free allocated memory (assume that the object lived before and gets reinitialized)
  if (_pixelData != nullptr) {
    delete[] _pixelData;
  }
  if (_renderSurface != nullptr) {
    delete _renderSurface;
  }
  // Point variables / assign values
  _pixelData = source._pixelData;
  _renderSurface = source._renderSurface;
  _bitmapBuffer = std::move(source._bitmapBuffer);  // source invalidated by moving
  _width = source._width;
  _height = source._height;
  _curRGB = source._curRGB;
  // Invalidate source
  source._pixelData = nullptr;
  source._renderSurface = nullptr;
  source._width = 0;
  source._height = 0;
  source._curRGB = 0;
  std::cout << "Moved '&operator=' instance " << &source << " to " << this << std::endl;
  return *this;
}

// Destructor
Graphics::~Graphics() {
  if (_pixelData != nullptr) {
    delete[] _pixelData;
  }
  _timer.Stop();
  std::cout << "_graphics deallocated: " << this << std::endl;
}

// Setters for timer
void Graphics::SetTimerOwner(wxFrame *frame) {
  _timer.SetOwner(frame);
};
void Graphics::InitLoop() {
  _timer.Start(5, wxTIMER_CONTINUOUS);  // 17 = approx. 60 frames per second; 10 = 100 frames per second
}
void Graphics::InitLoop(unsigned int t, bool oneShot) {  // t = milliseconds, oneSHot = wxTIMER_CONTINUOUS (while loop alternative) or wxTIMER_ONE_SHOT; https://docs.wxwidgets.org/trunk/classwx_timer.html
  _timer.Start(t, oneShot);
};

// Getters
wxWindow *Graphics::GetRenderSurface() {
  return _renderSurface;
}
wxBitmap *Graphics::GetBitmapBuffer() {
  return &(_bitmapBuffer);
}

// Behavioral methods
void Graphics::DrawToBuffer() {
  wxPaintDC dc(_renderSurface);  // TODO(SK): take a deeper look into rendering mechanism (Reminder for SK)
  if (_bitmapBuffer.IsOk()) {
    dc.DrawBitmap(_bitmapBuffer, 0, 0);
  }
}

void Graphics::RebuildBufferAndRefresh() {
  // Build the pixel buffer here, for this simple example just set all pixels to the same value and then increment that value.
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      _pixelData[3 * y * _width + 3 * x] = _curRGB;
      _pixelData[3 * y * _width + 3 * x + 1] = _curRGB;
      _pixelData[3 * y * _width + 3 * x + 2] = _curRGB;
    }
  }

  ++(_curRGB);
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