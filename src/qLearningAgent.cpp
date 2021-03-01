#include "qLearningAgent.h"

QLearningAgent::QLearningAgent() {}
QLearningAgent::~QLearningAgent() {}

double QLearningAgent::computeValueFromQValues(std::vector<double> state) { return 0; }

std::string QLearningAgent::computeActionFromQValues(std::vector<double> state) {
  return std::string();
}

void QLearningAgent::Update(std::vector<double> state, std::string action, std::vector<double> nextState, double reward) {}

double QLearningAgent::GetQValue(std::vector<double> state, std::string action) {
  return 0;
}

void QLearningAgent::SetQValue(std::vector<double> state, std::string action, double value) {}

std::string QLearningAgent::GetAction(std::vector<double> state) {
  return std::string();
}

std::string QLearningAgent::GetPolicy(std::vector<double> state) {
  return std::string();
}

double QLearningAgent::GetValue(std::vector<double> state) {
  return 0;
}

bool QLearningAgent::FlipCoin(int p) {
  return true;
}

std::string QLearningAgent::RandomChoice(std::vector<std::string> actions) {
  return std::string();
}
