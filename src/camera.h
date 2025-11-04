#pragma once

#include "pch.h"

class Camera{

public:
    Point getScreenPosition(int x, int y) const;
    void setPosition(int newX, int newY);
    void getPosition(int &outX, int &outY) const;

    void move(int deltaX, int deltaY){
        x += deltaX;
        y += deltaY;
    }

    void processEvent(const SDL_Event& event);

private:
    int x = 0;
    int y = 0;
};