#pragma once

#include "pch.h"
struct Material{

    SDL_Texture * texture = nullptr;
    SDL_Color color{255,255,255,255};
    SDL_FRect srcRect{0.0f,0.0f,0.0f,0.0f};
    glm::vec2 offset;
    float width = 0.0f;
    float height = 0.0f;

    bool filled = false;
    
};