#include "crawlingRobotEnvironment.h"

CrawlingRobotEnvironment::CrawlingRobotEnvironment(std::shared_ptr<CrawlingRobot> &crawlingRobot)
    : _crawlingRobot(crawlingRobot) {
  double minArmAngle, maxArmAngle, minHandAngle, maxHandAngle;

  std::tie(minArmAngle, maxArmAngle) = _crawlingRobot->GetMinAndMaxArmAngles();
  std::tie(minHandAngle, maxHandAngle) = _crawlingRobot->GetMinAndMaxHandAngles();

  double armIncrement = (maxArmAngle - minArmAngle) / (_nArmStates - 1);
  double handIncrement = (maxHandAngle - minHandAngle) / (_nHandStates - 1);

  for (int i = 0; i < _nArmStates; i++) {
    _armBuckets.push_back(minArmAngle + (armIncrement * i));
  }

  for (int i = 0; i < _nHandStates; i++) {
    _handBuckets.push_back(minHandAngle + (handIncrement * i));
  }

  Reset();
}

CrawlingRobotEnvironment::~CrawlingRobotEnvironment() {}
std::vector<double> CrawlingRobotEnvironment::GetCurrentState() { return _state; }

std::vector<std::string> CrawlingRobotEnvironment::GetPossibleActions(std::vector<double> &state) {
  std::vector<std::string> actions{};

  double currArmBucket = state[0];
  double currHandBucket = state[1];

  if (currArmBucket > 0) actions.push_back("arm-down");
  if (currArmBucket < _nArmStates - 1) actions.push_back("arm-up");
  if (currHandBucket > 0) actions.push_back("hand-down");
  if (currHandBucket < _nHandStates - 1) actions.push_back("hand-up");

  return actions;
}

std::pair<std::vector<double>, double> CrawlingRobotEnvironment::DoAction(std::string &action) {
  std::vector<double> nextState;
  double reward;

  Position oldPos = _crawlingRobot->GetRobotPosition();
  double armBucket = _state[0];
  double handBucket = _state[1];

  double armAngle, handAngle;
  std::tie(armAngle, handAngle) = _crawlingRobot->GetAngles();

  if (action == "arm-up") {
    double newArmAngle = _armBuckets[armBucket + 1];
    _crawlingRobot->MoveArm(newArmAngle);
    nextState[0] = armBucket + 1;
    nextState[1] = handBucket;
  }
  if (action == "arm-down") {
    double newArmAngle = _armBuckets[armBucket - 1];
    _crawlingRobot->MoveArm(newArmAngle);
    nextState[0] = armBucket - 1;
    nextState[1] = handBucket;
  }
  if (action == "hand-up") {
    double newHandAngle = _handBuckets[handBucket + 1];
    _crawlingRobot->MoveHand(newHandAngle);
    nextState[0] = armBucket;
    nextState[1] = handBucket + 1;
  }
  if (action == "hand-down") {
    double newHandAngle = _handBuckets[handBucket - 1];
    _crawlingRobot->MoveHand(newHandAngle);
    nextState[0] = armBucket;
    nextState[1] = handBucket - 1;
  }

  Position newPos = _crawlingRobot->GetRobotPosition();
  reward = newPos.x - oldPos.x;

  _state = nextState;
  return std::pair<std::vector<double>, double>(nextState, reward);
}

void CrawlingRobotEnvironment::Reset() {
  double armState = _nArmStates / 2;
  double handState = _nHandStates / 2;
  _state[0] = armState;
  _state[1] = handState;
  _crawlingRobot->SetAngles(_armBuckets[armState], _handBuckets[handState]);
  _crawlingRobot->_positions.push_back(20);
  _crawlingRobot->_positions.push_back(_crawlingRobot->GetRobotPosition().x);
}