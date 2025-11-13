#pragma once

#include <SDL3/SDL.h>
#include <managers/game_manager.h>
#include <state_machine/state_machine.h>
#include "libraries/renderer/renderer.h"

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

    void uiConsole();
    void uiStatistics();

    Statistic stats;
    StateMachine stateMachine;
    GameManager& gameManager = GameManager::getInstance();
    InputManager* input = InputManager::getInstance();
    Renderer renderer;

    void tempInit();
    
    
};