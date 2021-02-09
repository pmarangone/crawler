#include <crawler.h>

// CrawLingRobot(){}
// ~CrawLingRobot(){}

void CrawLingRobot::SetAngles(double armAngle, double handAngle) {
  _armAngle = armAngle;
  _handAngle = handAngle;
}

std::pair<double, double> CrawLingRobot::GetAngles() {
  return std::make_pair<int, int>(_armAngle, _handAngle);
}
Position CrawLingRobot::GetRobotPosition() {
  /*
   * returns the (x,y) coordinates
   * of the lower-left point of the
   * robot
   *
   * from cs188 crawler.py */
  return _robotPos;
}

void CrawLingRobot::MoveArm(double newArmAngle) {
  // TODO: rewrite message
  assert((newArmAngle < _maxArmAngle) &&
         "Crawling Robot: Arm Raised too high. Careful!");
  assert((newArmAngle > _minArmAngle) &&
         "Crawling Robot: Arm Raised too low. Careful!");

  // double oldArmAngle = _armAngle; <- use case?
  double disp = Displacement(_armAngle, _handAngle, newArmAngle, _handAngle);
  _robotPos.x = _robotPos.x + disp;
  _armAngle = newArmAngle;

  double lastPos = GetRobotPosition().x;
  _positions.push(lastPos);

  if (_positions.size() > 100) _positions.pop();
}
void CrawLingRobot::MoveHand(double newHandAngle) {
  // TODO: rewrite message
  assert((newHandAngle < _maxHandAngle) &&
         "Crawling Robot: Hand Raised too high. Careful!");
  assert((newHandAngle > _minHandAngle) &&
         "Crawling Robot: Hand Raised too low. Careful!");

  // double oldHandAngle = _handAngle; <- use case?
  double disp = Displacement(_armAngle, _handAngle, _armAngle, newHandAngle);
  _robotPos.x = _robotPos.x + disp;
  _handAngle = newHandAngle;

  double lastPos = GetRobotPosition().x;
  _positions.push(lastPos);
  if (_positions.size() > 100) _positions.pop();
}

std::pair<double, double> CrawLingRobot::GetMinAndMaxArmAngles() {
  return std::make_pair<int, int>(_minArmAngle, _maxArmAngle);
}
std::pair<double, double> CrawLingRobot::GetMinAndMaxHandAngles() {
  return std::make_pair<int, int>(_minHandAngle, _maxHandAngle);
}

// TODO: needs draw function
// double CrawLingRobot::GetRotationAngle() {
//   std::pair<int, int> arm = GetCosAndSin(_armAngle),
//                       hand = GetCosAndSin(_handAngle);

//   return 0;  
// }

std::pair<double, double> CrawLingRobot::GetCosAndSin(double angle) {
  double cosine = std::cos(angle);
  double sine = std::sin(angle);
  return std::make_pair<int, int>(cosine, sine);
}

// TODO needs draw function
// double CrawLingRobot::Displacement(double oldArmDegree, double oldHandDegree,
//                                    double armDegree, double handDegree);

// TODO
// void CrawLingRobot::draw(double stepCount, double stepDelay);