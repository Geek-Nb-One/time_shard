#pragma once

#include "pch.h"

const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;


class ControlManager{
public:
    void processInput(const SDL_Event* event);

    int getHorizontalDirection() const;
    int getVerticalDirection() const;

private:
    int keyPressed = 0;

    void processKey(SDL_Keycode key, bool pressed);

};