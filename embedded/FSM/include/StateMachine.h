#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#define MAX_TRANSITIONS 100

class Transition {
 private:
  State nextState;

 public:
  Transition(State nextState, int *func());
  State trigger();
};

class State {
 private:
  State getNextState();

 public:
  int addTransition();
  Transition transitions[MAX_TRANSITIONS];
};

class StateMachine {
 public:
  StateMachine(State startState);
  State currentState;
  State goToNextState();
};

#endif
