#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#define MAX_TRANSITIONS 100

class Transition {
 private:
  State nextState;

 public:
  Transition(State nextState, State *transitionEval());
  State trigger();
};

class State {
 private:
  int numTransitions = 0;
  State getNextState();

 public:
  int addTransition(Transition newTransition);
  Transition transitions[MAX_TRANSITIONS];
};

class StateMachine {
 public:
  StateMachine(State startState);
  State currentState;
  void goToNextState();
};

#endif
