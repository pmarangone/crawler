#ifndef CRAWLINGROBOTENVIRONMENT_H
#define CRAWLINGROBOTENVIRONMENT_H

#include <vector>

#include "crawlingRobot.h"

class CrawlingRobotEnvironment {
 public:
  CrawlingRobotEnvironment(std::shared_ptr<CrawlingRobot> &crawlingRobot);
  ~CrawlingRobotEnvironment();

  std::vector<double> GetCurrentState();
  std::vector<std::string> GetPossibleActions(std::vector<double> &state);
  std::pair<std::vector<double>, double> DoAction(std::string &action);
  void Reset();

  double _nArmStates = 9;
  double _nHandStates = 13;

  std::shared_ptr<CrawlingRobot> _crawlingRobot{nullptr};
  std::vector<double> _state{0, 0};

  std::vector<double> _armBuckets;
  std::vector<double> _handBuckets;
};

#endif /* CRAWLINGROBOTENVIRONMENT_H */
