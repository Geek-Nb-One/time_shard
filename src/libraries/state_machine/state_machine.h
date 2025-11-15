#pragma once


#include "state.h"
#include "pch.h"
#include <renderer/renderer.h>  

class StateMachine {
private:
    std::unique_ptr<State> currentState;
    std::unique_ptr<State> nextState;
    std::unordered_map<std::string, std::unique_ptr<State>> states;

    ts::Renderer * renderer = nullptr;

public:

    // Template method must stay in header
    template<typename T, typename... Args>
    void addState(const std::string& name, Args&&... args) {
        auto state = std::make_unique<T>(std::forward<Args>(args)...);
        state->create(this);  // Set the state machine reference
        states[name] = std::move(state);
    }
    
    void init(ts::Renderer* renderer);

    void changeState(const std::string& name);
    void update(float deltaTime);
    void render();
    void handleEvent(const SDL_Event* event);
    void destroy();
};