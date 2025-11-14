#include "app.h"

#include "libraries/game_object/game_object.h"
#include "libraries/game_object/component.h"
#include "libraries/game_object/transform.h"
#include "libraries/game_object/camera.h"

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

    gameManager.init();
    stateMachine.init();
    renderer.init();

    Console::log("Application initialized");
}

void App::loop()
{

    bool running = true;
    SDL_Event e;

    while (running)
    {

        Console::newFrame();

        static Uint64 lastTime = SDL_GetPerformanceCounter();
        Uint64 currentTime = SDL_GetPerformanceCounter();
        double deltaTime = (double)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
        lastTime = currentTime;

        static Uint64 frameCount = 0;
        static Uint64 lastFPSTime = SDL_GetTicks();
        Uint64 startFrameTime = SDL_GetTicks();

        while (SDL_PollEvent(&e))
        {

            processEvent(&e);
            if (e.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        update(static_cast<float>(deltaTime));

        // ImGui_ImplSDLRenderer3_NewFrame();
        // ImGui_ImplSDL3_NewFrame();
        // ImGui::NewFrame();

        // update(static_cast<float>(deltaTime));
        renderer.newFrame();
        
        uiConsole();
        
        // uiStatistics();

        stateMachine.render(renderer);

        uiFrameConsole();

        renderer.render();
        frameCount++;

        Uint64 currentFPSTime = SDL_GetTicks();
        stats.fps = static_cast<int>(frameCount * 1000 / (currentFPSTime - lastFPSTime + 1));
        stats.frameTimes.push_back(static_cast<int>(currentFPSTime - startFrameTime));
        stats.usage = (float)(currentFPSTime - startFrameTime) / (float)(1000.0f / 60);
        if (currentFPSTime - lastFPSTime >= 1000) // 1 second passed
        {
            frameCount = 0;
            lastFPSTime = currentFPSTime;
        }

        // gameManager.renderer().present();
    }
}

void App::cleanup()
{
    gameManager.destroy();
}

void App::processEvent(SDL_Event *event)
{

    gameManager.processEvent(event);
    stateMachine.handleEvent(event);
    if (Config::imGuiEnabled)
    {
        ImGui_ImplSDL3_ProcessEvent(event);
    }
}

void App::update(float deltaTime)
{
    input->update();
    stateMachine.update(deltaTime);
}

void App::uiConsole()
{
    ImGui::Begin("Console");
    ImGui::Text(Console::getLog().c_str());
    ImGui::End();
}

void App::uiStatistics()
{
    ImGui::Begin("Statistics");
    ImGui::Text("FPS: %d", stats.fps);
    ImGui::Text("CPU Usage: %.2f%%", stats.usage * 100.0f);
    int l = std::min((int)stats.frameTimes.size(), 120);

    std::vector<float> frameTimesFloat(stats.frameTimes.end() - l, stats.frameTimes.end());
    ImGui::PlotLines("Frame Times", frameTimesFloat.data(), frameTimesFloat.size(), 0, nullptr, 0.0f, 50.0f, ImVec2(0, 80));
    ImGui::End();
}

void App::uiFrameConsole()
{
    ImGui::Begin("Frame Console");
    ImGui::Text(Console::getFrameLog().c_str());
    ImGui::End();
}
