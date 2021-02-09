#define _USE_MATH_DEFINES

#include <cassert>   // assert
#include <chrono>    // time
#include <cmath>     // trig functions
#include <iostream>  // debug
#include <memory>    // unique_ptr
#include <queue>
#include <utility>  // pair
#include <vector>

struct State {
  double armBucket;
  double handBucket;
};

struct Position {
  double x;
  double y;
};

class CrawlingRobot {
 public:
  CrawlingRobot();
  ~CrawlingRobot();

  void SetAngles(double armAngle, double handAngle);
  std::pair<double, double> GetAngles();
  Position GetRobotPosition();
  void MoveArm(double newArmAngle);
  void MoveHand(double newHandAngle);

  std::pair<double, double> GetMinAndMaxArmAngles();
  std::pair<double, double> GetMinAndMaxHandAngles();
  double GetRotationAngle();
  std::pair<double, double> GetCosAndSin(double angle);

  /* */
  double Displacement(double oldArmDegree, double oldHandDegree,
                      double armDegree, double handDegree);
  void draw(double stepCount, double stepDelay);

  double _armAngle;
  double _handAngle;
  double _maxArmAngle;
  double _minArmAngle;
  double _maxHandAngle;
  double _minHandAngle;

  Position _robotPos;
  std::queue<int> _positions;
};

class CrawlingRobotEnvironment {
 public:
  CrawlingRobotEnvironment();
  CrawlingRobotEnvironment(
      CrawlingRobot crawlingRobot);  // TODO
  ~CrawlingRobotEnvironment();

  State GetCurrentState();
  std::vector<std::string> GetPossibleActions(State &state);
  std::pair<State, double> doAction(std::string &action);
  void Reset();

  double _nArmStates = 9;
  double _nHandStates = 13;

  std::unique_ptr<CrawlingRobot> _crawlingRobot;
  State _state;

  std::vector<int> _armBuckets;
  std::vector<int> _handBuckets;
};