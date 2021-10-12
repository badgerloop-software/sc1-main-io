#include <unistd.h>

#include <iostream>

#include "States.h"
#include "Transitions.h"
#include "i2c.h"
#include "mcp23017.h"

void print_state(State* state) {
  // printf("Device input 1 = %d\nDevice input 2 = %d\nestop = %s\n", devInput1,
  // devInput2, (hitEStop) ? "on" : "off");
  if (state == &state1) printf("In state 1\n");

  if (state == &state2) printf("In state 2\n");

  if (state == &state3) printf("In state 3\n");
  if (state == &eStop) printf("ESTOP\n");
}

int main() {
  // Set state 1's transitions
  state1.addTransition(&stop);
  state1.addTransition(&state1ToState3);
  state1.addTransition(&state1ToState2);
  state1.addTransition(&state1ToState1);

  // Set state2's transitions
  state2.addTransition(&stop);
  state2.addTransition(&state2ToState1);
  state2.addTransition(&state2ToState3);

  // // Set state3's transitions
  state3.addTransition(&stop);
  state3.addTransition(&state3ToState3);
  state3.addTransition(&state3ToState2);

  StateMachine machine1 = StateMachine(&state1);
  print_state(machine1.currentState);

  // 1 to 2
  devInput1 = 1;
  devInput2 = 1;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // state2 to state3
  devInput1 = 1;
  devInput2 = 100;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // state3 to state3
  devInput1 = 4;
  devInput2 = -1;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // state3 to state2
  devInput1 = 1;
  devInput2 = 1;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // // state2 to state1
  devInput1 = 24;
  devInput2 = 1;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // state1 to state1
  devInput1 = 1;
  devInput2 = 0;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // state1 to state3
  devInput1 = 0;
  devInput2 = 1;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // state3 to state2
  devInput1 = 1;
  devInput2 = 1;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // state2 to state1
  devInput1 = 1;
  devInput2 = 0;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // state1 to eStop
  hitEStop = true;
  machine1.goToNextState();
  print_state(machine1.currentState);

  // eStop has no transitions, but machine1 should stay in eStop
  machine1.goToNextState();
  print_state(machine1.currentState);

  return 0;
}
