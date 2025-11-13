#include "state.h"
#include "state_machine.h"  // Need full include to call methods

void State::create(StateMachine *sm)
{
    stateMachine = sm;

}

void State::changeState(const std::string &name)
{
    if (stateMachine) {
        stateMachine->changeState(name);
    }
}


