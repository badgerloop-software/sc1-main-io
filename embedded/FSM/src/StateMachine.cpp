#include "StateMachine.h"

#include <stdio.h>

// Transition methods

Transition::Transition(State* (*triggerFunc)(void)) {
  this->trigger = triggerFunc;
}

// State methods

State* State::getNextState() {
  State* stepState;

  for (int i = 0; i < this->numTransitions; i++) {
    Transition* transition = this->transitions[i];
    stepState = transition->trigger();
    if (stepState != 0) {
      return stepState;
    }
  }

  return this;  // Return the current State if no transitions returned a next
                // State
}

void State::addTransition(Transition* newTransition) {
  this->transitions[this->numTransitions] = newTransition;
  this->numTransitions++;
}

// StateMachine methods

StateMachine::StateMachine(State* startState) {
  this->currentState = startState;
}

void StateMachine::goToNextState() {
  this->currentState = this->currentState->getNextState();
}
