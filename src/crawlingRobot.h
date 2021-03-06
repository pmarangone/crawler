#ifndef CRAWLINGROBOT_H
#define CRAWLINGROBOT_H

#define _USE_MATH_DEFINES

#include <cassert>   // assert
#include <chrono>    // time
#include <cmath>     // trig functions
#include <iostream>  // debug
#include <memory>    // unique_ptr
#include <queue>     // deque
#include <utility>   // pair

class CrawlingRobot {
 public:
  CrawlingRobot();
  CrawlingRobot(const CrawlingRobot &source);
  CrawlingRobot &operator=(const CrawlingRobot &source);
  CrawlingRobot(CrawlingRobot &&source);
  CrawlingRobot &operator=(CrawlingRobot &&source);
  ~CrawlingRobot();

  // Getters & setters for robot variables
  void SetAngles(double armAngle, double handAngle);
  std::pair<double, double> GetMinAndMaxArmAngles();
  std::pair<double, double> GetMinAndMaxHandAngles();
  std::pair<double, double> GetCosAndSin(double angle);
  std::pair<double, double> GetAngles();
  double GetRotationAngle();
  std::pair<double, double> GetRobotPosition();

  // Robot update values
  void MoveArm(double newArmAngle);
  void MoveHand(double newHandAngle);
  /* */
  double Displacement(double oldArmDegree, double oldHandDegree,
                      double armDegree, double handDegree);
  /* Canvas */
  double _velAvg;
  double _lastStep;

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
  std::pair<double, double> _robotPos;

  /* Robot Arm */
  double _armLength;

  /* Robot Hand */
  double _handLength;

  // first-in first-out behavior
  std::deque<int> _positions;

  // temporary values
  double _groundHeight{196};   // same size as bottomPanelHeight
  double _groundY{500 - 196};  // windowHeight - groundHeight = top of bottomPanel
  int _windowWidth{900};
  int _windowHeight{500};
};

#endif /* CRAWLINGROBOT_H */
