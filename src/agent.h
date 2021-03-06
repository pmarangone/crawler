#ifndef AGENT_H
#define AGENT_H

#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

class ReinforcementAgent {
 public:
  ReinforcementAgent(std::function<std::vector<std::string>(std::pair<double, double>)> actionFn);
  ReinforcementAgent(int numTraining, double epsilon, double alpha, double gamma);
  ~ReinforcementAgent();
  std::vector<std::string> GetLegalActions(std::pair<int, int> state);
  void ObserveTransition(std::pair<int, int> state, std::string action, std::pair<int, int> nextState, double deltaReward);
  void StartEpisode();
  void StopEpisode();
  bool IsInTraning();
  bool IsInTesting();
  void SetEpsilon(double epsilon);
  void SetLearningRate(double alpha);
  void SetDiscount(double gamma);
  void DoAction(std::pair<int, int> state, std::string action);
  virtual void Update(std::pair<int, int> state, std::string action, std::pair<int, int> nextState, double deltaReward) = 0;

  std::function<std::vector<std::string>(std::pair<double, double>)> _actionFn;

  int _episodesSoFar{0};
  double _episodeRewards{0};
  double _accumTrainRewards{0};
  double _accumTestRewards{0};
  int _numTraining;
  double _epsilon;
  double _alpha;
  double _discount;

  // TODO: update all states from vector to pairs
  std::pair<int, int> _lastState{0, 0};
  std::string _lastAction;
};

#endif /* AGENT_H */