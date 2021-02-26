#include "crawlingRobot.h"

// TODO: decide how draw function is implemented
CrawlingRobot::CrawlingRobot() {
  _armAngle = _oldArmDegree = 0.0;
  _handAngle = _oldHandDegree = -M_PI / 6;

  _maxArmAngle = M_PI / 6;
  _minArmAngle = -M_PI / 6;

  _maxHandAngle = 0;
  _minHandAngle = -(5.0 / 6.0) * M_PI;

  /* Robot Body */
  _robotWidth = 80;
  _robotHeight = 40;
  _robotPos.x = 20;
  _robotPos.y = _groundY;

  /* Robot Arm */
  _armLength = 60;

  /* Robot Hand */
  _handLength = 40;

  _positions = std::deque<int>{0, 0};
  _lastStep = 0;
}

CrawlingRobot::CrawlingRobot(const CrawlingRobot &source) {
  _armAngle = source._armAngle;
  _oldArmDegree = source._oldArmDegree;
  _handAngle = source._handAngle;
  _oldHandDegree = source._oldHandDegree;
  _robotPos = source._robotPos;
  _positions = source._positions;
}
CrawlingRobot &CrawlingRobot::operator=(const CrawlingRobot &source) {
  _armAngle = source._armAngle;
  _oldArmDegree = source._oldArmDegree;
  _handAngle = source._handAngle;
  _oldHandDegree = source._oldHandDegree;
  _robotPos = source._robotPos;
  _positions = source._positions;

  return *this;
}

CrawlingRobot::CrawlingRobot(CrawlingRobot &&source) {
  _armAngle = source._armAngle;
  _oldArmDegree = source._oldArmDegree;
  _handAngle = source._handAngle;
  _oldHandDegree = source._oldHandDegree;
  _robotPos = source._robotPos;
  _positions = source._positions;
}

CrawlingRobot &CrawlingRobot::operator=(CrawlingRobot &&source) {
  _armAngle = source._armAngle;
  _oldArmDegree = source._oldArmDegree;
  _handAngle = source._handAngle;
  _oldHandDegree = source._oldHandDegree;
  _robotPos = source._robotPos;
  _positions = source._positions;

  return *this;
}

CrawlingRobot::~CrawlingRobot() {}

void CrawlingRobot::SetAngles(double armAngle, double handAngle) {
  _armAngle = armAngle;
  _handAngle = handAngle;
}

std::pair<double, double> CrawlingRobot::GetAngles() {
  return std::pair<double, double>(_armAngle, _handAngle);
}

Position CrawlingRobot::GetRobotPosition() {
  /*
   * returns the (x,y) coordinates
   * of the lower-left point of the
   * robot
   *
   * from cs188 crawler.py */
  return _robotPos;
}

void CrawlingRobot::MoveArm(double newArmAngle) {
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
  _positions.push_back(lastPos);

  if (_positions.size() > 100) _positions.pop_front();
}

void CrawlingRobot::MoveHand(double newHandAngle) {
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
  _positions.push_back(lastPos);
  if (_positions.size() > 100) _positions.pop_front();
}

std::pair<double, double> CrawlingRobot::GetMinAndMaxArmAngles() {
  return std::pair<double, double>(_minArmAngle, _maxArmAngle);
}

std::pair<double, double> CrawlingRobot::GetMinAndMaxHandAngles() {
  return std::pair<double, double>(_minHandAngle, _maxHandAngle);
}

double CrawlingRobot::GetRotationAngle() {
  double armCos, armSin, handCos, handSin;
  std::tie(armCos, armSin) = GetCosAndSin(_armAngle);
  std::tie(handCos, handSin) = GetCosAndSin(_handAngle);

  double x = _armLength * armCos + _handLength * handCos + _robotWidth;
  double y = _armLength * armSin + _handLength * handSin + _robotHeight;

  if (y < 0) {
    return atan(-y / x);
  }
  return 0.0;
}

std::pair<double, double> CrawlingRobot::GetCosAndSin(double angle) {
  double cosine = std::cos(angle);
  double sine = std::sin(angle);
  return std::pair<double, double>(cosine, sine);
}

double CrawlingRobot::Displacement(double oldArmDegree, double oldHandDegree, double armDegree, double handDegree) {
  double armCos, armSin, oldArmCos, oldArmSin;
  double handCos, handSin, oldHandCos, oldHandSin;

  std::tie(armCos, armSin) = GetCosAndSin(armDegree);
  std::tie(oldArmCos, oldArmSin) = GetCosAndSin(oldArmDegree);
  std::tie(handCos, handSin) = GetCosAndSin(handDegree);
  std::tie(oldHandCos, oldHandSin) = GetCosAndSin(oldHandDegree);

  double xOld = _armLength * oldArmCos * _handLength * oldHandCos * _robotWidth;
  double yOld = _armLength * oldArmSin * _handLength * oldHandSin * _robotHeight;

  double x = _armLength * armCos * _handLength * handCos * _robotWidth;
  double y = _armLength * armSin * _handLength * handSin * _robotHeight;

  if (y < 0) {
    if (yOld <= 0) {
      return sqrt((xOld * xOld) + (yOld * yOld)) - sqrt((x * x) + (y * y));
    }
    return (xOld - yOld * (x - xOld) / (yOld - y)) - sqrt((x * x) + (y * y));
  } else {
    if (yOld >= 0) {
      return 0.0;
    }
    return -(x - y * (xOld - x) / (yOld - y)) +
           sqrt((xOld * xOld) + (yOld * yOld));
  }

  assert(0 == 1 && "Should never happen!");
  return 0.0;
}

// Getters & setters for control variables (spin controls)
double CrawlingRobot::GetLearningRate() { return this->_learningRate; }
double CrawlingRobot::GetStepDelay() { return this->_stepDelay; }
double CrawlingRobot::GetDiscount() { return this->_discount; }
double CrawlingRobot::GetEpsilon() { return this->_epsilon; }

void CrawlingRobot::SetLearningRate(double learningRate) {
  this->_learningRate = learningRate;
  std::cout << "Robot's _learningRate: " << this->_learningRate << std::endl;  // TODO(SK): delete when tested
}
void CrawlingRobot::SetStepDelay(double stepDelay) {
  this->_stepDelay = stepDelay;
  std::cout << "Robot's _stepDelay: " << this->_stepDelay << std::endl;  // TODO(SK): delete when tested
}
void CrawlingRobot::SetDiscount(double discount) {
  this->_discount = discount;
  std::cout << "Robot's _discount: " << this->_discount << std::endl;  // TODO(SK): delete when tested
}
void CrawlingRobot::SetEpsilon(double epsilon) {
  this->_epsilon = epsilon;
  std::cout << "Robot's _epsilon: " << this->_epsilon << std::endl;  // TODO(SK): delete when tested
}