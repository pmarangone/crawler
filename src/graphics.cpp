#include "graphics.h"

// clang-format off
BEGIN_EVENT_TABLE(Graphics, wxWindow)
  EVT_PAINT(Graphics::paintEvent)
END_EVENT_TABLE();
// clang-format on

// Default constructor
Graphics::Graphics() : _width(1),
                       _height(1) {}

// Overloaded default constructor
Graphics::Graphics(wxPanel *parent, std::shared_ptr<CrawlingRobot> &robot, int width, int height)
    : wxWindow(parent,
               wxID_ANY,
               wxDefaultPosition,
               wxSize(width, height)),
      _width(width),
      _height(height),
      _robot(robot) {
  this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

// Move constructor
Graphics::Graphics(Graphics &&source) {
  // Point variables / assign values
  _width = source._width;
  _height = source._height;
  _robot = std::move(source._robot);
  // _timer left out (no copying policy imposed by wxWidgets)
  // Invalidate source
  source._width = 0;
  source._height = 0;
  std::cout << "Moved instance " << &source << " to " << this << std::endl;
}

// Move assignment operator constructor
Graphics &Graphics::operator=(Graphics &&source) {
  if (this == &source) {
    return *this;
  }
  // Point variables / assign values
  _width = source._width;
  _height = source._height;
  _robot = std::move(source._robot);
  // Invalidate source
  source._width = 0;
  source._height = 0;
  std::cout << "Moved '&operator=' instance " << &source << " to " << this << std::endl;
  return *this;
}

// Destructor
Graphics::~Graphics() {
  _timer.Stop();
  std::cout << "_graphics deallocated: " << this << std::endl;
}

// Setters for timer
void Graphics::SetTimerOwner(wxFrame *frame) {
  _timer.SetOwner(frame);
}
void Graphics::InitLoop() {
  _timer.Start(17, wxTIMER_CONTINUOUS);  // 17 = approx. 60 frames per second; 10 = 100 frames per second
}
void Graphics::InitLoop(unsigned int t, bool isOneShot) {  // t = milliseconds, oneSHot = wxTIMER_CONTINUOUS (while loop alternative) or wxTIMER_ONE_SHOT; https://docs.wxwidgets.org/trunk/classwx_timer.html
  _timer.Start(t, isOneShot);
}

// Behavioral methods
void Graphics::paintEvent(wxPaintEvent &event) {
  wxPaintDC dc(this);
  Render(dc);
}

void Graphics::paintNow() {
  wxClientDC dc(this);
  Render(dc);
}

void Graphics::Notify() {
  Refresh();
}

void Graphics::Render(wxDC &dc) {
  int x1 = _robot->_robotPos.first, y1 = _robot->_robotPos.second;
  x1 = x1 % _robot->_windowWidth;

  double rotationAngle = _robot->GetRotationAngle();
  double cosRot, sinRot;
  std::tie(cosRot, sinRot) = _robot->GetCosAndSin(rotationAngle);

  assert((y1 == _robot->_groundY) && "Value initialization inconsistent");

  int x2 = x1 + _robot->_robotWidth * cosRot;
  int y2 = y1 - _robot->_robotWidth * sinRot;

  int x3 = x1 - _robot->_robotHeight * sinRot;
  int y3 = y1 - _robot->_robotHeight * cosRot;

  int x4 = x3 + cosRot * _robot->_robotWidth;
  int y4 = y3 - sinRot * _robot->_robotWidth;

  wxPoint points[4];
  points[0] = wxPoint(x1, y1);
  points[1] = wxPoint(x2, y2);
  points[2] = wxPoint(x4, y4);
  points[3] = wxPoint(x3, y3);

  /* robot body */
  dc.SetBrush(*wxGREEN_BRUSH);
  dc.DrawPolygon(WXSIZEOF(points), points, 0, 0);

  /* robot arm */
  double armCos, armSin;
  std::tie(armCos, armSin) = _robot->GetCosAndSin(rotationAngle + _robot->_armAngle);
  int xArm = x4 + _robot->_armLength * armCos;
  int yArm = y4 - _robot->_armLength * armSin;

  dc.SetBrush(*wxYELLOW_BRUSH);
  dc.DrawLine(x4, y4, xArm, yArm);

  /* robot hand */
  double handCos, handSin;
  std::tie(handCos, handSin) = _robot->GetCosAndSin(_robot->_handAngle + rotationAngle);
  int xHand = xArm + _robot->_handLength * handCos;
  int yHand = yArm - _robot->_handLength * handSin;

  dc.SetBrush(*wxRED_BRUSH);
  dc.DrawLine(xArm, yArm, xHand, yHand);

  _robot->_robotPos.first += 1;
}