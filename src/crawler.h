#define _USE_MATH_DEFINES

#include <chrono>    // time
#include <cmath>     // trig functions
#include <iostream>  // debug
#include <utility>   // pair
#include <cassert>
#include <queue>

struct State {
  double armBucket;
  double handBucket;
};

struct Position {
  double x;
  double y;
};

class CrawLingRobot {
  
public:

  CrawLingRobot();
  ~CrawLingRobot();

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

template <class State>
class CrawlingRobotEnvironment {
 public:
  CrawlingRobotEnvironment();
  // CrawlingRobotEnvironment(CrawlingRobot);  // TODO
  ~CrawlingRobotEnvironment();

  State GetCurrentState();
  State GetPossibleActions(State state);
  std::pair<double, double> Reset();
};