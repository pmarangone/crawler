#include "robotEnv.h"

RobotEnvironment::RobotEnvironment(std::shared_ptr<Robot> robot)
    : _robot(robot) {
  double minArmAngle, maxArmAngle, minHandAngle, maxHandAngle;

  std::tie(minArmAngle, maxArmAngle) = _robot->GetMinAndMaxArmAngles();
  std::tie(minHandAngle, maxHandAngle) = _robot->GetMinAndMaxHandAngles();

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

RobotEnvironment::~RobotEnvironment() {}
std::pair<int, int> RobotEnvironment::GetCurrentState() {
  return _state;
}

std::vector<std::string> RobotEnvironment::GetPossibleActions(std::pair<int, int> state) {
  std::vector<std::string> actions;

  int currArmBucket = state.first;
  int currHandBucket = state.second;

  if (currArmBucket > 0) {
    actions.push_back("arm-down");
  }
  if (currArmBucket < _nArmStates - 1) {
    actions.push_back("arm-up");
  }
  if (currHandBucket > 0) {
    actions.push_back("hand-down");
  }
  if (currHandBucket < _nHandStates - 1) {
    actions.push_back("hand-up");
  }
  return actions;
}

std::pair<std::pair<double, double>, double> RobotEnvironment::DoAction(std::string action) {
  std::pair<int, int> nextState;
  double reward;

  assert((_robot != nullptr) && "_robot is a nullptr");

  std::pair<double, double> oldPos = _robot->GetRobotPosition();

  int armBucket = _state.first;
  int handBucket = _state.second;

  double armAngle, handAngle;
  std::tie(armAngle, handAngle) = _robot->GetAngles();

  if (action == "arm-up") {
    double newArmAngle = _armBuckets[armBucket + 1];
    _robot->MoveArm(newArmAngle);
    nextState.first = armBucket + 1;
    nextState.second = handBucket;
  }
  if (action == "arm-down") {
    double newArmAngle = _armBuckets[armBucket - 1];
    _robot->MoveArm(newArmAngle);
    nextState.first = armBucket - 1;
    nextState.second = handBucket;
  }
  if (action == "hand-up") {
    double newHandAngle = _handBuckets[handBucket + 1];
    _robot->MoveHand(newHandAngle);
    nextState.first = armBucket;
    nextState.second = handBucket + 1;
  }
  if (action == "hand-down") {
    double newHandAngle = _handBuckets[handBucket - 1];
    _robot->MoveHand(newHandAngle);
    nextState.first = armBucket;
    nextState.second = handBucket - 1;
  }

  std::pair<double, double> newPos = _robot->GetRobotPosition();
  reward = newPos.first - oldPos.first;

  _state = nextState;
  return std::pair<std::pair<double, double>, double>(nextState, reward);
}

void RobotEnvironment::Reset() {
  int armState = _nArmStates / 2;
  int handState = _nHandStates / 2;

  _state.first = armState;
  _state.second = handState;

  _robot->SetAngles(_armBuckets[armState], _handBuckets[handState]);

  _robot->_positions.clear();
  _robot->_positions.push_back(20);
  _robot->_positions.push_back(_robot->GetRobotPosition().first);
}