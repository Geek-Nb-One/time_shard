#pragma once

#include "render_manager.h"
#include "input_manager.h"

class GameManager
{

public:
    static GameManager &getInstance();

    void init();
    void destroy();

    void log(const char* message); 
    void processEvent(SDL_Event* event);

    RenderManager &renderer();
    // InputManager &input();

    std::string getLog() const;

private:
    GameManager() = default;
    ~GameManager() = default;
    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;

    bool isInitialized = false;

    RenderManager _renderer;
    // InputManager _control;

    void checkInitialization() const;

    std::string _log;
};