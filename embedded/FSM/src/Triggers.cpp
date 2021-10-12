#include "Triggers.h"

#include "States.h"

bool hitEStop = false;
int devInput1 = 0;
int devInput2 = 0;

State* eStopTrigger() { return hitEStop ? &eStop : 0; }

State* state1To3Trigger() { return (devInput1 < devInput2) ? &state3 : 0; }

State* state1To2Trigger() { return (devInput1 == devInput2) ? &state2 : 0; }

State* state1To1Trigger() { return (devInput1 > devInput2) ? &state1 : 0; }

State* state2To3Trigger() { return (devInput1 < devInput2) ? &state3 : 0; }

State* state2To1Trigger() { return (devInput1 >= devInput2) ? &state1 : 0; }

State* state3To2Trigger() { return (devInput1 == devInput2) ? &state2 : 0; }

State* state3To3Trigger() { return (devInput1 != devInput2) ? &state3 : 0; }
