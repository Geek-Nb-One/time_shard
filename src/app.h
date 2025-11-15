#pragma once

#include <SDL3/SDL.h>
#include <state_machine/state_machine.h>
#include "libraries/renderer/renderer.h"
#include <managers/input_manager.h>

struct Statistic{
    std::vector<int> frameTimes;
    int fps = 0;
    float usage = 0.0f;
};


class App{

public:

    void run();

private:
    void init();
    void loop();
    void cleanup();
    void processEvent(SDL_Event* event);
    void update(float deltaTime);
    void render();


    void uiConsole();
    void uiStatistics();
    void uiFrameConsole();

    Statistic stats;
    StateMachine stateMachine;
    InputManager* input = InputManager::getInstance();
    ts::Renderer renderer;

    
    
};