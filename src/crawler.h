#define _USE_MATH_DEFINES

#include <chrono>    // time
#include <cmath>     // trig functions
#include <iostream>  // debug
#include <utility>   // pair

struct NextState {
  double armBucket;
  double handBucket;
};

/* instead of using tuples, its possible to use structs */
// struct Position {
//   double x;
//   double y;
// };

class CrawLingRobot {
  CrawLingRobot();
  ~CrawLingRobot();

  void SetAngles(double armAngle, double handAngle);
  std::pair<double, double> GetAngles();
  std::pair<double, double> GetRobotPosition();
  void MoveArm(double newArmAngle);
  void MoveHnad();

  std::pair<double, double> GetMinAndMaxArmAngles();
  std::pair<double, double> GetMinAndMaxHandAngles();
  double GetRotationAngle();
  std::pair<double, double> GetCosAndSin(double angle);

  /* */
  double Displacement(double oldArmDegree, double oldHandDegree,
                      double armDegree, double handDegree);
  void draw(double stepCount, double stepDelay);
};

template <class State, class action>
class CrawlingRobotEnvironment {
 public:
  CrawlingRobotEnvironment();
  // CrawlingRobotEnvironment(CrawlingRobot);  // TODO
  ~CrawlingRobotEnvironment();

  State GetCurrentState();
  State GetPossibleActions(State state);
  std::pair<double, double> Reset();
};