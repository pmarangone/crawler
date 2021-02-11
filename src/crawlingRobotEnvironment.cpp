#include "crawlingRobotEnvironment.h"

// TODO
CrawlingRobotEnvironment::CrawlingRobotEnvironment() { ; }

// TODO
CrawlingRobotEnvironment::~CrawlingRobotEnvironment() { ; }

CrawlingRobotEnvironment::CrawlingRobotEnvironment(
    CrawlingRobot crawlingRobot) {
  _crawlingRobot = std::make_unique<CrawlingRobot>();
  std::pair<int, int> minMaxArmAngles = _crawlingRobot->GetMinAndMaxArmAngles();
  std::pair<int, int> minMaxHandAngles =
      _crawlingRobot->GetMinAndMaxHandAngles();

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

std::pair<State, double> CrawlingRobotEnvironment::doAction(
    std::string &action) {
  State nextState;
  double reward;

  Position oldPos = _crawlingRobot->GetRobotPosition();
  double armBucket = _state.armBucket;
  double handBucket = _state.handBucket;

  std::pair<int, int> angles = _crawlingRobot->GetAngles();
  double armAngle = angles.first;
  double handAngle = angles.second;

  if (action == "arm-up") {
    double newArmAngle = _armBuckets[armBucket + 1];
    _crawlingRobot->MoveArm(newArmAngle);
    nextState.armBucket = armBucket + 1;
    nextState.handBucket = handBucket;
  }
  if (action == "arm-down") {
    double newArmAngle = _armBuckets[armBucket - 1];
    _crawlingRobot->MoveArm(newArmAngle);
    nextState.armBucket = armBucket - 1;
    nextState.handBucket = handBucket;
  }
  if (action == "hand-up") {
    double newHandAngle = _handBuckets[handBucket + 1];
    _crawlingRobot->MoveHand(newHandAngle);
    nextState.armBucket = armBucket;
    nextState.handBucket = handBucket + 1;
  }
  if (action == "hand-down") {
    double newHandAngle = _handBuckets[handBucket - 1];
    _crawlingRobot->MoveHand(newHandAngle);
    nextState.armBucket = armBucket;
    nextState.handBucket = handBucket - 1;
  }

  Position newPos = _crawlingRobot->GetRobotPosition();
  reward = newPos.x - oldPos.x;

  _state = nextState;
  return std::pair<State, double>(nextState, reward);
}

void CrawlingRobotEnvironment::Reset() {
  double armState = _nArmStates / 2;
  double handState = _nHandStates / 2;
  _state.armBucket = armState;
  _state.handBucket = handState;
  _crawlingRobot->SetAngles(_armBuckets[armState], _handBuckets[handState]);
  _crawlingRobot->_positions.push_back(20);
  _crawlingRobot->_positions.push_back(_crawlingRobot->GetRobotPosition().x);
}