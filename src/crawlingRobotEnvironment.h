#ifndef CRAWLINGROBOTENVIRONMENT_H
#define CRAWLINGROBOTENVIRONMENT_H

#include <mutex>
#include <thread>
#include <tuple>
#include <vector>

#include "crawlingRobot.h"

class CrawlingRobotEnvironment {
 public:
  CrawlingRobotEnvironment(std::shared_ptr<CrawlingRobot> crawlingRobot);
  ~CrawlingRobotEnvironment();

  std::pair<int, int> GetCurrentState();
  std::vector<std::string> GetPossibleActions(std::pair<int, int> state);
  std::pair<std::pair<double, double>, double> DoAction(std::string action);
  void Reset();

  constexpr static double _nArmStates{9};
  constexpr static double _nHandStates{13};

  std::shared_ptr<CrawlingRobot> _crawlingRobot{nullptr};
  std::pair<int, int> _state{0, 0};

  std::vector<double> _armBuckets;
  std::vector<double> _handBuckets;
};

#endif /* CRAWLINGROBOTENVIRONMENT_H */
