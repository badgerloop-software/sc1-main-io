#include <unistd.h>

#include <iostream>

#include "i2c.h"
#include "mcp23017.h"

int main() {
    bool hitEStop = false;
    int devInput1 = 0;
    int devInput2 = 1;

    State state1;
    State state2;
    State state3;
    State eStop;

    // Transition from any state to eStop
    Transition stop = Transition(eStop, State triggerFunc() {
        return (hitEStop ? this->nextState : NULL);
    });

    // Set state1's transitions
    state1->addTransition(stop);
    state1->addTransition(Transition(state3, State triggerFunc() {
        return ((devInput1 < devInput2) ? this->nextState : NULL);
    }));
    state1->addTransition(Transition(state2, State triggerFunc() {
        return ((devInput1 == devInput2) ? this->nextState : NULL);
    }));
    state1->addTransition(Transition(state1, State triggerFunc() {
        return ((devInput1 > devInput2) ? this->nextState : NULL);
    }));

    // Set state2's transitions
    state2->addTransition(stop);
    state2->addTransition(Transition(state3, State triggerFunc() {
        return ((devInput1 < devInput2) ? this->nextState : NULL);
    }));
    state2->addTransition(Transition(state1, State triggerFunc() {
        return (((devInput1 > devInput2) || (devInput1 == devInput2)) ? this->nextState : NULL);
    }));

    // Set state3's transitions
    state3->addTransition(stop);
    state3->addTransition(Transition(state2, State triggerFunc() {
        return ((devInput1 == devInput2) ? this->nextState : NULL);
    }));
    state3->addTransition(Transition(state3, State triggerFunc() {
        return (((devInput1 > devInput2) || (devInput1 < devInput2)) ? this->nextState : NULL);
    }));


    StateMachine machine1 = StateMachine(state1);

    // Should start at state1
    printf(machine1->currentState == state1);

    // state1 to state2
    devInput1 = 1;
    devInput2 = 1;
    machine1->goToNextState();
    printf(machine1->currentState == state2);

    // state2 to state3
    devInput1 = 0;
    devInput2 = 1;
    machine1->goToNextState();
    printf(machine1->currentState == state3);

    // state3 to state3
    machine1->goToNextState();
    printf(machine1->currentState == state3);

    // state3 to state3
    devInput1 = 1;
    devInput2 = 0;
    machine1->goToNextState();
    printf(machine1->currentState == state3);

    // state3 to state2
    devInput1 = 1;
    devInput2 = 1;
    machine1->goToNextState();
    printf(machine1->currentState == state2);

    // state2 to state1
    machine1->goToNextState();
    printf(machine1->currentState == state1);

    // state1 to state3
    devInput1 = 0;
    devInput2 = 1;
    machine1->goToNextState();
    printf(machine1->currentState == state3);

    // state3 to state2
    devInput1 = 1;
    devInput2 = 1;
    machine1->goToNextState();
    printf(machine1->currentState == state2);

    // state2 to state1
    devInput1 = 1;
    devInput2 = 0;
    machine1->goToNextState();
    printf(machine1->currentState == state1);

    // state1 to state1
    devInput1 = 1;
    devInput2 = 0;
    machine1->goToNextState();
    printf(machine1->currentState == state1);

    // state1 to eStop
    hitEStop = true;
    machine1->goToNextState();
    printf(machine1->currentState == eStop);

    // eStop has no transitions, but machine1 should stay in eStop
    machine1->goToNextState();
    printf(machine1->currentState == eStop);

}
