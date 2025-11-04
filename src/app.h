#pragma once

#include <SDL3/SDL.h>
#include "window.h"
#include "control_manager.h"



struct Statistic{
    int fps = 0;
};


class App{

public:

    void run();

private:
    void init();
    void loop();
    void cleanup();
    void processEvent(SDL_Event* event);

    Window window;
    ControlManager controlManager;

    Statistic stats;

};