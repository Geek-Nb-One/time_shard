#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <utility>
#include <vector>
#include <iostream>
#include <cmath>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <stdexcept>
#include <map>
#include <algorithm>
#include <set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlrenderer3.h>

typedef std::pair<int, int> Point;

#include "config.h"

class Console
{

public:
    static void log(std::string message)
    {
        _log += message + "\n";
    }
    static void log(const char *message)
    {
        _log += std::string(message) + "\n";
    }
    static std::string getLog()
    {
        return _log;
    }

    static void logFrame(const char* message)
    {
        _frame_log += std::string(message) + "\n";
    }

    static void logFrame(std::string message)
    {
        _frame_log += message + "\n";
    }
    static std::string getFrameLog()
    {
        return _frame_log;
    }
    static void newFrame() {
        _frame_log = "";

    }

private:
    static inline std::string _log;
    static inline std::string _frame_log;
};
