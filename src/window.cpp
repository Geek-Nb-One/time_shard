#include "window.h"
#include <stdexcept>
#include <iostream>
#include <cstring>



void Window::init(const char *title, int width, int height,uint32_t flags)
{

          // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to initialize SDL");
    }

    // Create window
    _window = SDL_CreateWindow(title, width, height, flags);
    if (!_window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL window");
    }

    
}

void Window::processEvent(SDL_Event *event)
{
    if (event->type == SDL_EVENT_WINDOW_RESIZED)
    {
        resize(event->window.data1, event->window.data2);
    } 
}

void Window::cleanup()
{
    if (_window)
    {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    SDL_Quit();
}

SDL_Renderer *Window::initRenderer(const char * name)
{
    // Try to create hardware accelerated renderer first
    SDL_Renderer *renderer = SDL_CreateRenderer(_window, name);
    
    if (!renderer)
    {
        std::cerr << "Hardware accelerated renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        std::cerr << "Falling back to software renderer..." << std::endl;
        
        // Fallback to software renderer
        renderer = SDL_CreateRenderer(_window, "software");
        if (!renderer)
        {
            std::cerr << "Software renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            throw std::runtime_error("Failed to create any SDL renderer");
        }
    }
    
    // Check renderer properties in SDL3
    const char* renderer_name = SDL_GetRendererName(renderer);
    if (renderer_name)
    {
        std::cout << "Using renderer: " << renderer_name << std::endl;
        
        // Check if it's a hardware accelerated renderer
        if (strcmp(renderer_name, "software") != 0)
        {
            std::cout << "Hardware acceleration: LIKELY ENABLED" << std::endl;
        }
        else
        {
            std::cout << "Hardware acceleration: DISABLED (using software)" << std::endl;
        }
    }
    
    SDL_SetRenderVSync(renderer, true);
    
    return renderer;
}

void Window::resize(int width, int height)
{
    if (_window)
    {
        SDL_SetWindowSize(_window, width, height);
        std::cout << "Window resized to " << width << "x" << height << std::endl;
    }
}
