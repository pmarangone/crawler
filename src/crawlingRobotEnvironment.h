#include "crawlingRobot.h"

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