#include "input_manager.h"


InputManager *InputManager::instance = nullptr;

InputManager *InputManager::getInstance()
{
    return instance == nullptr ? instance = new InputManager() : instance;
}

void InputManager::init()
{
    actionActive[ControlAction::MOVE_LEFT] = false;
    actionActive[ControlAction::MOVE_RIGHT] = false;
    actionActive[ControlAction::MOVE_UP] = false;
    actionActive[ControlAction::MOVE_DOWN] = false;
    actionActive[ControlAction::CAMERA_ATTACH_TOGGLE] = false;
    actionActive[ControlAction::START_ACTION] = false;

    initGamepad();

    Console::log("Input Manager initialized");
}

void InputManager::destroy()
{
}

void InputManager::update()
{
    updatePressedAction();
    updateTriggerAction();

    triggered.clear();
}

void InputManager::processEvent(const SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        processKey(event->key.key, true);
    }
    else if (event->type == SDL_EVENT_KEY_UP)
    {
        processKey(event->key.key, false);
    }
    else if (event->type == SDL_EVENT_GAMEPAD_ADDED)
    {
        addGamepad(event->cdevice.which);
    }
    else if (event->type == SDL_EVENT_GAMEPAD_REMOVED)
    {
        removeGamepad(event->cdevice.which);
    }else if(event->type == SDL_EVENT_GAMEPAD_AXIS_MOTION)
    {
        processAxisEvent(event);
    }
}

int InputManager::getHorizontalDirection() const
{
    int direction = 0;
    if (isActive(ControlAction::MOVE_LEFT))
        direction -= 1;
    if (isActive(ControlAction::MOVE_RIGHT))
        direction += 1;
    return direction;
}

int InputManager::getVerticalDirection() const
{
    int direction = 0;
    if (isActive(ControlAction::MOVE_DOWN))
        direction += 1;
    if (isActive(ControlAction::MOVE_UP))
        direction -= 1;
    return direction;
}

bool InputManager::isActive(ControlAction action) const
{
    return actionActive[action];
}

void InputManager::processKey(SDL_Keycode key, bool event_pressed)
{

    pressed[key] = event_pressed;

    if (event_pressed)
    {
        activated[key] = true;
    }
    else
    {
        if (activated[key] == true)
        {
            activated[key] = false;
            triggered[key] = true;
        }
    }
}

void InputManager::processAxisEvent(const SDL_Event *event)
{
    if (event->gaxis.axis == SDL_GAMEPAD_AXIS_LEFTX)
    {
       leftXvalue = event->gaxis.value;
    }else if(event->gaxis.axis == SDL_GAMEPAD_AXIS_LEFTY)
    {
      leftYvalue = event->gaxis.value;
    }
}

void InputManager::updateTriggerAction()
{
    actionActive[ControlAction::CAMERA_ATTACH_TOGGLE] = keyIsTriggered(SDLK_SPACE);
    actionActive[ControlAction::START_ACTION] = keyIsTriggered(SDLK_RETURN);
}

void InputManager::updatePressedAction()
{

    actionActive[ControlAction::MOVE_LEFT] = keyIsPressed(SDLK_A) || keyIsPressed(SDLK_LEFT) || leftAxisMoved(ControlAction::MOVE_LEFT);
    actionActive[ControlAction::MOVE_RIGHT] = keyIsPressed(SDLK_D) || keyIsPressed(SDLK_RIGHT) || leftAxisMoved(ControlAction::MOVE_RIGHT);
    actionActive[ControlAction::MOVE_UP] = keyIsPressed(SDLK_W) || keyIsPressed(SDLK_UP) || leftAxisMoved(ControlAction::MOVE_UP);
    actionActive[ControlAction::MOVE_DOWN] = keyIsPressed(SDLK_S) || keyIsPressed(SDLK_DOWN) || leftAxisMoved(ControlAction::MOVE_DOWN);
}

bool InputManager::keyIsPressed(SDL_Keycode key)
{
    return keyState(key, pressed);
}
bool InputManager::keyIsActivated(SDL_Keycode key)
{
    return keyState(key, activated);
}
bool InputManager::keyIsTriggered(SDL_Keycode key)
{
    return keyState(key, triggered);
}

bool InputManager::keyState(SDL_Keycode key, std::map<SDL_Keycode, bool> &stateMap)
{
    if (stateMap.find(key) != stateMap.end())
    {
        return stateMap[key];
    }
    return false;
}

void InputManager::addGamepad(SDL_JoystickID id)
{
    // Implementation for adding a gamepad
    auto gamepad_ptr = SDL_OpenGamepad(id);
    if (gamepad_ptr != nullptr && gamepad == nullptr)
    {
        gamepadID = id;
        gamepad = gamepad_ptr;
        gamepadActive = true;
        Console::log(std::string("Gamepad connected: ") + std::to_string(id));
    }
}

void InputManager::removeGamepad(SDL_JoystickID id)
{
    // Implementation for removing a gamepad
    if (gamepadActive && gamepadID == id)
    {
        SDL_CloseGamepad(gamepad);
        gamepad = nullptr;
        gamepadActive = false;
        Console::log(std::string("Gamepad disconnected: ") + std::to_string(id));
    }
}

void InputManager::initGamepad()
{

    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD);

    int count = 0;
    SDL_JoystickID *ids = SDL_GetGamepads(&count);
    Console::log(std::string("Detected ") + std::to_string(count) + " gamepads.");
    for (int i = 0; i < count; i++)
    {
        if (!gamepadActive)
        {
            Console::log(std::string("Trying to initialize gamepad: ") + std::to_string(ids[i]));
            addGamepad(ids[i]);
        }   
    }
}
