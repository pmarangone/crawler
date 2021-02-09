#include "crawler.h"

CrawlingRobot::CrawlingRobot() { ; }
CrawlingRobot::~CrawlingRobot() { ; }

void CrawlingRobot::SetAngles(double armAngle, double handAngle) {
  _armAngle = armAngle;
  _handAngle = handAngle;
}

std::pair<double, double> CrawlingRobot::GetAngles() {
  return std::make_pair<int, int>(_armAngle, _handAngle);
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
  _positions.push(lastPos);

  if (_positions.size() > 100) _positions.pop();
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
  _positions.push(lastPos);
  if (_positions.size() > 100) _positions.pop();
}

std::pair<double, double> CrawlingRobot::GetMinAndMaxArmAngles() {
  return std::make_pair<int, int>(_minArmAngle, _maxArmAngle);
}
std::pair<double, double> CrawlingRobot::GetMinAndMaxHandAngles() {
  return std::make_pair<int, int>(_minHandAngle, _maxHandAngle);
}

// TODO: needs draw function
double CrawlingRobot::GetRotationAngle() {
  // std::pair<int, int> arm = GetCosAndSin(_armAngle),
  //                     hand = GetCosAndSin(_handAngle);

  return 0;
}

std::pair<double, double> CrawlingRobot::GetCosAndSin(double angle) {
  double cosine = std::cos(angle);
  double sine = std::sin(angle);
  return std::make_pair<int, int>(cosine, sine);
}

// TODO needs draw function
double CrawlingRobot::Displacement(double oldArmDegree, double oldHandDegree,
                                   double armDegree, double handDegree) {
  return 0;
}

// TODO
void CrawlingRobot::draw(double stepCount, double stepDelay){};

CrawlingRobotEnvironment::CrawlingRobotEnvironment() { ; }
CrawlingRobotEnvironment::~CrawlingRobotEnvironment() { ; }

CrawlingRobotEnvironment::CrawlingRobotEnvironment(
    CrawlingRobot crawlingRobot) {
  _crawlingRobot = std::make_unique<CrawlingRobot>();
  std::pair<int, int> minMaxArmAngles =
      _crawlingRobot->GetMinAndMaxArmAngles();  // (min, max)
  std::pair<int, int> minMaxHandAngles =
      _crawlingRobot->GetMinAndMaxHandAngles();  // (min, max)

  double armIncrement =
      (minMaxArmAngles.second - minMaxArmAngles.first) / (_nArmStates - 1);
  double handIncrement =
      (minMaxHandAngles.second - minMaxHandAngles.first) / (_nHandStates - 1);

  for (int i = 0; i < _nArmStates; i++) {
    _armBuckets.push_back(minMaxArmAngles.first + (armIncrement * i));
  }

  for (int i = 0; i < _nHandStates; i++) {
    _handBuckets.push_back(minMaxHandAngles.first + (handIncrement * i));
  }

  Reset();
}

State CrawlingRobotEnvironment::GetCurrentState() { return _state; }

std::vector<std::string> CrawlingRobotEnvironment::GetPossibleActions(
    State &state) {
  std::vector<std::string> actions{};

  double currArmBucket = state.armBucket;
  double currHandBucket = state.handBucket;

  if (currArmBucket > 0) actions.push_back("arm-down");
  if (currArmBucket < _nArmStates - 1) actions.push_back("arm-up");
  if (currHandBucket > 0) actions.push_back("hand-down");
  if (currHandBucket < _nHandStates - 1) actions.push_back("hand-up");

  return actions;
}

// TODO: fix return types
// std::pair<State, double> CrawlingRobotEnvironment::doAction(std::string
// &action) {

//   State nextState;
//   double reward;

//   Position oldPos = _crawlingRobot->GetRobotPosition();
//   double armBucket = _state.armBucket;
//   double handBucket = _state.handBucket;

//   std::pair<int,int> angles = _crawlingRobot->GetAngles();
//   double armAngle = angles.first;
//   double handAngle = angles.second;

//   if (action == "arm-up") {
//     double newArmAngle = _armBuckets[armBucket + 1];
//     _crawlingRobot->MoveArm(newArmAngle);
//     nextState.armBucket = armBucket + 1;
//     nextState.handBucket = handBucket;
//   }
//   if (action == "arm-down") {
//     double newArmAngle = _armBuckets[armBucket - 1];
//     _crawlingRobot->MoveArm(newArmAngle);
//     nextState.armBucket = armBucket -1;
//     nextState.handBucket = handBucket;
//   }
//   if (action == "hand-up") {
//     double newHandAngle = _handBuckets[handBucket + 1];
//     _crawlingRobot->MoveHand(newHandAngle);
//     nextState.armBucket = armBucket;
//     nextState.handBucket = handBucket + 1;
//   }
//   if (action == "hand-down") {
//     double newHandAngle = _handBuckets[handBucket -1];
//     _crawlingRobot->MoveHand(newHandAngle);
//     nextState.armBucket = armBucket;
//     nextState.handBucket = handBucket - 1;
//   }

//   Position newPos = _crawlingRobot->GetRobotPosition();
//   reward = newPos.x - oldPos.x;

//   _state = nextState;
//   return std::make_pair<State, double>(nextState, reward);
// }

void CrawlingRobotEnvironment::Reset() {
  double armState = _nArmStates / 2;
  double handState = _nHandStates / 2;
  _state.armBucket = armState;
  _state.handBucket = handState;
  _crawlingRobot->SetAngles(_armBuckets[armState], _handBuckets[handState]);
  _crawlingRobot->_positions.push(20);
  _crawlingRobot->_positions.push(_crawlingRobot->GetRobotPosition().x);
}