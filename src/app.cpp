#include "app.h"

#include <iostream>
#include <stdexcept>


#include <SDL3_image/SDL_image.h>
#include "camera.h"

const char * APP_TITLE = "Time Shard";
const char * WINDOW_NAME = "Time Shard Window";

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
    window.init(WINDOW_NAME, 1920, 1080, SDL_WINDOW_RESIZABLE|SDL_WINDOW_FULLSCREEN);
}

void App::loop()
{

    int CAMERA_SPEED = 5;

    bool running = true;
    SDL_Event e;

    Camera camera{768,432};


    camera.setPosition(0,0);
    SDL_Renderer *renderer = window.initRenderer("opengl");

    SDL_SetRenderLogicalPresentation(renderer, 768, 432, SDL_LOGICAL_PRESENTATION_LETTERBOX);


    //Load Map
    SDL_Texture* texture = IMG_LoadTexture(renderer, "D:/Users/User/Documents/game_studio/projects/time_shard/assets/arts/ground_cave_24px_1.png");
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    
    if (!texture)
    {
        throw std::runtime_error("Failed to load texture: " + std::string(SDL_GetError()));
    }

    int textureIndex = map.addTile(texture, SDL_FRect{0,0,24,24});

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if ((i+j)% 2 == 0)
            {
                map.setTile(i, j, textureIndex);
            }
        }
    }

    while (running)
    {
        static Uint64 frameCount = 0;
        static Uint64 lastTime = SDL_GetTicks();
        
        SDL_RenderClear(renderer);

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
        }

        camera.move(controlManager.getHorizontalDirection() * CAMERA_SPEED, controlManager.getVerticalDirection() * CAMERA_SPEED);
        
        map.draw(renderer, camera);

        SDL_RenderPresent(renderer);
        
        frameCount++;
        Uint64 currentTime = SDL_GetTicks();
        stats.fps = static_cast<int>(frameCount * 1000 / (currentTime - lastTime + 1));
        if (currentTime - lastTime >= 1000) // 1 second passed
        {
            frameCount = 0;
            lastTime = currentTime;
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
    controlManager.processInput(event);

}
