#pragma once

#include <SDL3/SDL.h>


class Window{

public:

    void init(const char* title, int width, int height, uint32_t flags = 0);
    void processEvent(SDL_Event* event);
    void cleanup();

    SDL_Renderer* initRenderer(const char * name =nullptr);

private:
    SDL_Window * _window =nullptr;
    void resize(int width, int height);

};