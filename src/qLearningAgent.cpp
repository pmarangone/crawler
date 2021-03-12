#include "qLearningAgent.h"

QLearningAgent::QLearningAgent(std::function<std::vector<std::string>(std::pair<double, double>)> actionFn)
    : ReinforcementAgent(actionFn), _actionFn(actionFn) {}
QLearningAgent::~QLearningAgent() {}

double QLearningAgent::computeValueFromQValues(std::pair<int, int> state) {
  double maxQ = INT_MIN;

  std::vector<std::string> legalActions = GetLegalActions(state);
  if (legalActions.empty()) {
    return 0.0;
  }

  for (auto action : legalActions) {
    auto qValue = GetQValue(state, action);
    if (qValue > maxQ) {
      maxQ = qValue;
    }
  }
  return maxQ;
}

std::string QLearningAgent::computeActionFromQValues(std::pair<int, int> state) {
  std::vector<std::string> legalActions = GetLegalActions(state);
  if (legalActions.empty()) return NULL;

  double optiQ = INT_MIN;
  std::string optiAct;
  for (auto action : legalActions) {
    double tempQ = GetQValue(state, action);
    if (optiQ < tempQ) {
      optiQ = tempQ;
      optiAct = action;
    }
  }

  return optiAct;
}

void QLearningAgent::Update(std::pair<int, int> state, std::string action, std::pair<int, int> nextState, double reward) {
  double oldQ = GetQValue(state, action);
  double sample = reward + (_discount * GetValue(nextState));
  double newQVal = ((1 - _alpha) * oldQ) + (_alpha * sample);
  SetQValue(state, action, newQVal);
}

double QLearningAgent::GetQValue(std::pair<int, int> state, std::string action) {
  std::string index = std::to_string(state.first) + std::to_string(state.second) + action;
  return _values[index];
}

void QLearningAgent::SetQValue(std::pair<int, int> state, std::string action, double value) {
  std::string index = std::to_string(state.first) + std::to_string(state.second) + action;
  _values[index] = value;
}

std::string QLearningAgent::GetAction(std::pair<int, int> state) {
  std::vector<std::string> legalActions = GetLegalActions(state);
  std::string action{};

  bool route = FlipCoin(_epsilon);
  if (route) {
    action = RandomChoice(legalActions);
  } else {
    action = computeActionFromQValues(state);
  }

  return action;
}

std::string QLearningAgent::GetPolicy(std::pair<int, int> state) {
  return computeActionFromQValues(state);
}

double QLearningAgent::GetValue(std::pair<int, int> state) {
  return computeValueFromQValues(state);
}

bool QLearningAgent::FlipCoin(double p) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> d(0, 1);
  double x = d(gen);
  return x < p;
}

std::string QLearningAgent::RandomChoice(std::vector<std::string> actions) {
  assert((!actions.empty()) && "Invalid operation. List cannot be empty");

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> d(0, actions.size() - 1);

  int idx = d(gen);
  return actions[idx];
}
