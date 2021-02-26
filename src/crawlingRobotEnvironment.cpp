#include "crawlingRobotEnvironment.h"

CrawlingRobotEnvironment::CrawlingRobotEnvironment(std::shared_ptr<CrawlingRobot> &crawlingRobot) : _crawlingRobot(crawlingRobot) {
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

  double armAngle, handAngle;
  std::tie(armAngle, handAngle) = _crawlingRobot->GetAngles();

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