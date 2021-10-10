#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#define MAX_TRANSITIONS 100

class State;

class Transition {
 public:
  Transition(State* (*triggerFunc)(void));
  State* (*trigger)(void);
};

class State {
 private:
  int numTransitions = 0;

 public:
  State* getNextState();
  void addTransition(Transition* newTransition);
  Transition* transitions[MAX_TRANSITIONS];
};

class StateMachine {
 public:
  StateMachine(State* startState);
  State* currentState;
  void goToNextState();
};

#endif
