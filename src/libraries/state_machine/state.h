#pragma once

#include "../../pch.h"
#include <renderer/renderer.h>

// Forward declaration to avoid circular dependency
class StateMachine;

class State{
private:
    StateMachine* stateMachine = nullptr;

public:
    virtual ~State() = default;
    
    void create(StateMachine* sm);
    
    virtual void enter() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer& renderer) = 0;
    virtual void handleEvent(const SDL_Event* event) = 0;
    virtual void exit() = 0;

    void changeState(const std::string& name);

};