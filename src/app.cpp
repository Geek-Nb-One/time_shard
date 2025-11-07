#include "app.h"

#include <iostream>
#include <stdexcept>

#include <SDL3_image/SDL_image.h>

#include "libraries/state_machine/resource.h"
#include "libraries/state_machine/test_state.h"

const char *APP_TITLE = "Time Shard";
const char *WINDOW_NAME = "Time Shard Window";

void App::run()
{

    try
    {
        init();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Failed to initialize application: " << e.what() << std::endl;
        return;
    }
    try
    {
        loop();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Error during main loop: " << e.what() << std::endl;
    }

    cleanup();
}

void App::init()
{
    int WIDTH = 768;
    int HEIGHT = 432;

    window.init(WINDOW_NAME, 1920, 1080, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN);
    resource.renderer = window.initRenderer("opengl");
    resource.controlManager = new ControlManager();
    
    SDL_SetRenderLogicalPresentation(resource.renderer, WIDTH, HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    stateMachine.setResource(&resource);
    stateMachine.addState<TestState>("TestState");
    stateMachine.changeState("TestState");
}

void App::loop()
{

    bool running = true;
    SDL_Event e;

    while (running)
    {
        static Uint64 lastTime = SDL_GetPerformanceCounter();
        Uint64 currentTime = SDL_GetPerformanceCounter();
        double deltaTime = (double)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
        lastTime = currentTime;

        static Uint64 frameCount = 0;
        static Uint64 lastFPSTime = SDL_GetTicks();

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE)
            {
                running = false;
            }

            processEvent(&e);
            stateMachine.handleEvent(e);
        }

        stateMachine.update(static_cast<float>(deltaTime));
        stateMachine.render();

        frameCount++;
        Uint64 currentFPSTime = SDL_GetTicks();
        stats.fps = static_cast<int>(frameCount * 1000 / (currentFPSTime - lastFPSTime + 1));
        if (currentFPSTime - lastFPSTime >= 1000) // 1 second passed
        {
            frameCount = 0;
            lastFPSTime = currentFPSTime;
        }
    }
}

void App::cleanup()
{
    window.cleanup();
}

void App::processEvent(SDL_Event *event)
{
    window.processEvent(event);
    resource.controlManager->processInput(event);
}
