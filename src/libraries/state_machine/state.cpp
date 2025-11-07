#include "state.h"
#include "state_machine.h"  // Need full include to call methods

void State::create(StateMachine *sm, Resource *res)
{
    stateMachine = sm;
    resource = res;
    init();

}

void State::changeState(const std::string &name)
{
    if (stateMachine) {
        stateMachine->changeState(name);
    }
}

SDL_Renderer* State::getRenderer(){
    return resource->renderer;
}
