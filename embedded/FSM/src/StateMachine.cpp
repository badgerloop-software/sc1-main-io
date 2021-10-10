#include "StateMachine.h"

// Transition methods

Transition::Transition(State nextState, State *triggerFunc()) {
    this->nextState = nextState;
    this->trigger = triggerFunc;
}

// State methods

State State::getNextState() {
    State stepState;

    for(int i = 0; i < sizeof(this->transitions); i++) {
        stepState = this->transitions[i]->trigger();
        if(stepState != NULL) {
            return stepState;
        }
    }

    return this; // Return the current State if no transitions returned a next State
}

void State::addTransition(Transition newTransition) {
    this->transitions[this->numTransitions] = newTransition;
    this->numTransitions++;
}

// StateMachine methods

StateMachine::StateMachine(State startState) {
    this->currentState = startState;
}

void StateMachine::goToNextState() {
    this->currentState = this->currentState->getNextState();
}