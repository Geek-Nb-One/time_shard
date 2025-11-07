#include "state_machine.h"

void StateMachine::setResource(Resource *res)
{
    resource = res;
}

void StateMachine::changeState(const std::string &name)
{
    auto it = states.find(name);
    if (it != states.end()) {
        nextState = std::move(it->second);
    }
}

void StateMachine::update(float deltaTime) {
    // Handle state transitions
    if (nextState) {
        if (currentState) {
            currentState->exit();
        }
        currentState = std::move(nextState);
        currentState->enter();
        nextState.reset();
    }
    
    // Update current state
    if (currentState) {
        currentState->update(deltaTime);
    }
}

void StateMachine::render() {
    if (currentState) {
        currentState->render();
    }
}

void StateMachine::handleEvent(const SDL_Event& event) {
    if (currentState) {
        currentState->handleEvent(event);
    }
}