#ifndef QLEARNINGAGENT_H
#define QLEARNINGAGENT_H

#include <cassert>
#include <climits>
#include <functional>  // std::mem_fn
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "agent.h"

class QLearningAgent : public ReinforcementAgent {
 public:
  // Constructor & Destructor
  QLearningAgent();
  ~QLearningAgent();

  //
  double computeValueFromQValues(std::vector<double> state);
  std::string computeActionFromQValues(std::vector<double> state);
  void Update(std::vector<double> state, std::string action, std::vector<double> nextState, double reward) override;
  // Getter and Setters
  void SetQValue(std::vector<double> state, std::string action, double value);
  double GetValue(std::vector<double> state);
  double GetQValue(std::vector<double> state, std::string action);
  std::string GetAction(std::vector<double> state);
  std::string GetPolicy(std::vector<double> state);
  // utils
  bool FlipCoin(int p);
  std::string RandomChoice(std::vector<std::string> actions);

  std::function<std::vector<std::string>(std::vector<int>)> _actionFn;
  std::unordered_map<std::string, double> _values;
};

#endif /* QLEARNINGAGENT_H */