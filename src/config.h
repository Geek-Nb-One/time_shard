#pragma once

#include <SDL3/SDL.h>

struct Config{
    static constexpr const char* WINDOW_TITLE = "Time Shard";
    static constexpr const char* WINDOW_NAME = "Time Shard Window";
    static constexpr int WINDOW_WIDTH = 1920;
    static constexpr int WINDOW_HEIGHT = 1080;
    static constexpr int LOGICAL_WIDTH = 768;
    static constexpr int LOGICAL_HEIGHT = 432;
    static constexpr uint32_t WINDOW_FLAGS = SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN;
    static constexpr SDL_RendererLogicalPresentation LOGICAL_PRESENTATION_FLAGS = SDL_LOGICAL_PRESENTATION_LETTERBOX;
    static constexpr const char* RENDERER_NAME = "opengl";
    static constexpr bool imGuiEnabled = true;
};
