#pragma once


#include "state.h"
#include "../pch.h"

class StateMachine {
private:
    std::unique_ptr<State> currentState;
    std::unique_ptr<State> nextState;
    std::unordered_map<std::string, std::unique_ptr<State>> states;
    Resource* resource;
public:

    // Template method must stay in header
    template<typename T>
    void addState(const std::string& name) {
        auto state = std::make_unique<T>();
        state->create(this, resource);  // Set the state machine reference
        states[name] = std::move(state);
    }

    void setResource(Resource* res);
    
    void changeState(const std::string& name);
    void update(float deltaTime);
    void render();
    void handleEvent(const SDL_Event& event);
};