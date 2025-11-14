#pragma once

#include "pch.h"

enum ControlAction
{
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    CAMERA_ATTACH_TOGGLE
};

// const int LEFT = 0;
// const int RIGHT = 1;
// const int UP = 2;
// const int DOWN = 3;
// const int CAMERA_ATTACH_TOGGLE = 4;

class InputManager
{
public:
    static InputManager *getInstance();

public:
    void init();
    void destroy();

    void update();

    void processEvent(const SDL_Event *event);

    int getHorizontalDirection() const;
    int getVerticalDirection() const;

    bool isActive(ControlAction action) const;

private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) = delete;
    static InputManager *instance;

    std::map<SDL_Keycode, bool> activated;
    std::map<SDL_Keycode, bool> triggered;
    std::map<SDL_Keycode, bool> pressed;
    bool actionActive[5];
    int leftXvalue = 0;
    int leftYvalue = 0;

    void processKey(SDL_Keycode key, bool event_pressed);

    void processAxisEvent(const SDL_Event *event);

    void updatePressedAction();
    void updateTriggerAction();

    bool keyIsPressed(SDL_Keycode key);
    bool keyIsActivated(SDL_Keycode key);
    bool keyIsTriggered(SDL_Keycode key);

    bool leftAxisMoved(ControlAction action) const
    {
        switch (action)
        {
        case ControlAction::MOVE_RIGHT:
            return leftXvalue > deadZone;
            break;
        case ControlAction::MOVE_LEFT:
            return leftXvalue < -deadZone;
            break;
        case ControlAction::MOVE_UP:
            return leftYvalue < -deadZone;
            break;
        case ControlAction::MOVE_DOWN:
            return leftYvalue > deadZone;
            break;
        default:
            return false;
        }
    }

    bool keyState(SDL_Keycode key, std::map<SDL_Keycode, bool> &stateMap);

    bool gamepadActive = false;
    SDL_JoystickID gamepadID;
    SDL_Gamepad *gamepad = NULL;

    void addGamepad(SDL_JoystickID id);
    void removeGamepad(SDL_JoystickID id);
    void initGamepad();

    int deadZone = 8000;
};