#include "agent.h"

ReinforcementAgent::ReinforcementAgent(std::function<std::vector<std::string>(std::pair<double, double>)> actionFn) : _actionFn(actionFn) {}

ReinforcementAgent::ReinforcementAgent(int numTraining, double epsilon, double alpha, double gamma)
    : _numTraining(numTraining), _epsilon(epsilon), _alpha(alpha), _discount(gamma) {
}

ReinforcementAgent::~ReinforcementAgent() {}

std::vector<std::string> ReinforcementAgent::GetLegalActions(std::pair<int, int> state) {
  return _actionFn(state);
}

void ReinforcementAgent::ObserveTransition(std::pair<int, int> state, std::string action, std::pair<int, int> nextState, double deltaReward) {
  _episodeRewards += deltaReward;
  Update(state, action, nextState, deltaReward); /* QLearningAgent must override this function in order to it work */
}

void ReinforcementAgent::StartEpisode() {
  _lastState.first = 0;
  _lastState.second = 0;
  _lastAction = "";
  _episodeRewards = 0;
}

void ReinforcementAgent::StopEpisode() {
  if (_episodesSoFar < _numTraining) {
    _accumTrainRewards += _episodeRewards;
  } else {
    _accumTestRewards += _episodeRewards;
  }

  _episodesSoFar += 1;

  if (_episodesSoFar >= _numTraining) {
    _epsilon = 0;
    _alpha = 0;
  }
}

bool ReinforcementAgent::IsInTraning() {
  return _episodesSoFar < _numTraining;
}

bool ReinforcementAgent::IsInTesting() {
  return !IsInTraning();
}

void ReinforcementAgent::SetEpsilon(double epsilon) {
  _epsilon = epsilon;
}
void ReinforcementAgent::SetLearningRate(double alpha) {
  _alpha = alpha;
}
void ReinforcementAgent::SetDiscount(double gamma) {
  _discount = gamma;
}
void ReinforcementAgent::DoAction(std::pair<int, int> state, std::string action) {
  _lastState = state;
  _lastAction = action;
}