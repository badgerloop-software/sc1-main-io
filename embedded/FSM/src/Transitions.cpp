#include "Transitions.h"

Transition stop = Transition(&eStopTrigger);
Transition state1ToState3 = Transition(&state1To3Trigger);
Transition state1ToState2 = Transition(&state1To2Trigger);
Transition state1ToState1 = Transition(&state1To1Trigger);
Transition state2ToState1 = Transition(&state2To1Trigger);
Transition state2ToState3 = Transition(&state2To3Trigger);
Transition state3ToState2 = Transition(&state3To2Trigger);
Transition state3ToState3 = Transition(&state3To3Trigger);
