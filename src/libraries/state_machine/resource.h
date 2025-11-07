#pragma once

#include "../pch.h"
#include "../control_manager.h"

struct Resource {

    SDL_Renderer* renderer = nullptr;
    ControlManager* controlManager = nullptr;    
};