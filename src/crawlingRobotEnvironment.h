#ifndef CRAWLINGROBOTENVIRONMENT_H
#define CRAWLINGROBOTENVIRONMENT_H

#include <vector>

#include "crawlingRobot.h"

class CrawlingRobotEnvironment {
  CrawlingRobotEnvironment() = delete;

 public:
  CrawlingRobotEnvironment(std::shared_ptr<CrawlingRobot> &crawlingRobot);
  ~CrawlingRobotEnvironment();

  State GetCurrentState();
  std::vector<std::string> GetPossibleActions(State &state);
  std::pair<State, double> doAction(std::string &action);
  void Reset();

  double _nArmStates = 9;
  double _nHandStates = 13;

  std::shared_ptr<CrawlingRobot> _crawlingRobot{nullptr};
  State _state;

  std::vector<int> _armBuckets;
  std::vector<int> _handBuckets;
};

#endif /* CRAWLINGROBOTENVIRONMENT_H */
