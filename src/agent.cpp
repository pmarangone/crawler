#include "agent.h"

ReinforcementAgent::ReinforcementAgent() {}

ReinforcementAgent::ReinforcementAgent(int numTraining = 100, double epsilon = 0.5, double alpha = 0.5, double gamma = 1)
    : _numTraining(numTraining), _epsilon(epsilon), _alpha(alpha), _discount(gamma) {}

ReinforcementAgent::~ReinforcementAgent() {}

std::vector<std::string> ReinforcementAgent::GetLegalActions(std::vector<double> state) {
  return std::vector<std::string>();
}

void ReinforcementAgent::ObserveTransition(std::vector<double> state, std::string action, std::vector<double> nextState, double deltaReward) {}

void ReinforcementAgent::StartEpisode() {}

void ReinforcementAgent::StopEpisode() {}

bool ReinforcementAgent::IsInTraning() {
  return true;
}

bool ReinforcementAgent::IsInTesting() {
  return true;
}

void ReinforcementAgent::SetEpsilon(double epsilon) {}
void ReinforcementAgent::SetLearningRate(double alpha) {}
void ReinforcementAgent::SetDiscount(double gamma) {}
void ReinforcementAgent::DoAction(std::vector<double> state, std::string action) {}