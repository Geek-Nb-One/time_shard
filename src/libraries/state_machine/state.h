#pragma once

#include "../pch.h"
#include "resource.h"

// Forward declaration to avoid circular dependency
class StateMachine;

class State{
private:
    StateMachine* stateMachine = nullptr;
    Resource* resource;

public:
    virtual ~State() = default;
    

    void create(StateMachine* sm, Resource* res);
    
    virtual void enter() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void handleEvent(const SDL_Event& event) = 0;
    virtual void exit() = 0;
    virtual void init() = 0;

    void changeState(const std::string& name);

    SDL_Renderer* getRenderer();
    ControlManager* getControlManager() {
        return resource->controlManager;
    }
};