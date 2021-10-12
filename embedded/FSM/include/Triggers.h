#ifndef __TRIGGERS_H__
#define __TRIGGERS_H__
#include "StateMachine.h"

extern bool hitEStop;
extern int devInput1;
extern int devInput2;

State* eStopTrigger();
State* state1To3Trigger();
State* state1To2Trigger();
State* state1To1Trigger();
State* state2To3Trigger();
State* state2To1Trigger();
State* state3To2Trigger();
State* state3To3Trigger();

#endif
