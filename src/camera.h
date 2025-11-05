#pragma once

#include "pch.h"

class Camera
{

public:
    Camera(int width, int height);

    Point getScreenPosition(int x, int y) const;
    void setPosition(int newX, int newY);
    void getPosition(int &outX, int &outY) const;

    void move(int deltaX, int deltaY);

    void processEvent(const SDL_Event &event);

    int getWidth() const;
    int getHeight() const;

private:
    int x = 0;
    int y = 0;
    int width = 800;
    int height = 600;
};