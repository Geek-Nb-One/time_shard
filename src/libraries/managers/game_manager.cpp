#include "game_manager.h"

GameManager &GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

void GameManager::init()
{
    if (!isInitialized)
    {
        // _renderer.init();
        // _control.init();
        isInitialized = true;
    }
}

void GameManager::destroy()
{
    // _renderer.destroy();
    // _control.destroy();
}

void GameManager::log(const char *message)
{
    _log += std::string(message) + "\n";
}

void GameManager::processEvent(SDL_Event *event)
{
    // _control.processEvent(event);
    // _renderer.processEvent(event);
}

void GameManager::checkInitialization() const
{
    if (!isInitialized)
        throw std::runtime_error("GameManager not initialized");
}

RenderManager &GameManager::renderer()
{
    checkInitialization();
    return _renderer;
};
// InputManager &GameManager::input()
// {
//     checkInitialization();
//     return _control;
// }
std::string GameManager::getLog() const
{
    return _log;
};