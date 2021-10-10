#include "Transitions.h"

Transition stop = Transition(&eStopTrigger);
Transition state1ToState3 = Transition(&state1To3Trigger);
Transition state1ToState2 = Transition(&state1To2Trigger);
Transition state1ToState1 = Transition(&state1To1Trigger);
