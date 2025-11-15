#include "state_machine.h"

#include "scene_state.h"

void StateMachine::init(ts::Renderer* renderer)
{
    this->renderer = renderer;

    addState<SceneState>("scene", renderer);

    changeState("scene");
}

void StateMachine::changeState(const std::string &name)
{
    auto it = states.find(name);
    if (it != states.end()) {
        nextState = std::move(it->second);
        Console::log("Changing state to: " + name);
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

void StateMachine::handleEvent(const SDL_Event* event) {
    if (currentState) {
        currentState->handleEvent(event);
    }
}

void StateMachine::destroy()
{
}
