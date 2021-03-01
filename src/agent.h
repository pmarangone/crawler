#ifndef AGENT_H
#define AGENT_H

#include <functional>
#include <string>
#include <vector>

class ReinforcementAgent {
 public:
  ReinforcementAgent();
  ReinforcementAgent(int numTraining, double epsilon, double alpha, double gamma);
  ~ReinforcementAgent();
  std::vector<std::string> GetLegalActions(std::vector<double> state);
  void ObserveTransition(std::vector<double> state, std::string action, std::vector<double> nextState, double deltaReward);
  void StartEpisode();
  void StopEpisode();
  bool IsInTraning();
  bool IsInTesting();
  void SetEpsilon(double epsilon);
  void SetLearningRate(double alpha);
  void SetDiscount(double gamma);
  void DoAction(std::vector<double> state, std::string action);
  virtual void Update(std::vector<double> state, std::string action, std::vector<double> nextState, double deltaReward) = 0;

  std::function<std::vector<std::string>(std::vector<int>)> _actionFn;

  int _episodesSoFar{0};
  double _episodeRewards{0};
  double _accumTrainRewards{0};
  double _accumTestRewards{0};
  int _numTraining;
  double _epsilon;
  double _alpha;
  double _discount;

  std::vector<double> _lastState;
  std::string _lastAction;
};

#endif /* AGENT_H */