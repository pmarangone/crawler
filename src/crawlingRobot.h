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

  /* Canvas */
  double velAvg;
  double lastStep;

  /* Arm and Hand Degrees */
  double _armAngle;
  double _handAngle;

  double _maxArmAngle;
  double _minArmAngle;
  double _maxHandAngle;
  double _minHandAngle;

  double _oldArmDegree;
  double _oldHandDegree;

  /* Robot Body */
  double _robotWidth;
  double _robotHeight;
  Position _robotPos;

  /* Robot Arm */
  double _armLength;

  /* Robot Hand */
  double _handLength;

  // first-in first-out behavior
  std::deque<int> _positions;
};

