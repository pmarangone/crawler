#ifndef QLEARNINGAGENT_H
#define QLEARNINGAGENT_H

#include <cassert>
#include <climits>
#include <functional>  // std::mem_fn
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "agent.h"

class QLearningAgent : public ReinforcementAgent {
 public:
  // Constructor & Destructor
  QLearningAgent(std::function<std::vector<std::string>(std::pair<double, double>)> actionFn);
  ~QLearningAgent();

  //
  double computeValueFromQValues(std::pair<int, int> state);
  std::string computeActionFromQValues(std::pair<int, int> state);
  void Update(std::pair<int, int> state, std::string action, std::pair<int, int> nextState, double reward) override;
  // Getter and Setters
  void SetQValue(std::pair<int, int> state, std::string action, double value);
  double GetValue(std::pair<int, int> state);
  double GetQValue(std::pair<int, int> state, std::string action);
  std::string GetAction(std::pair<int, int> state);
  std::string GetPolicy(std::pair<int, int> state);
  // utils
  bool FlipCoin(double p);
  std::string RandomChoice(std::vector<std::string> actions);

  std::function<std::vector<std::string>(std::pair<double, double>)> _actionFn;
  std::unordered_map<std::string, double> _values;
};

#endif /* QLEARNINGAGENT_H */