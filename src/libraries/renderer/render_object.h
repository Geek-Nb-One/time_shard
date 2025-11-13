#pragma once

#include "../../pch.h"

struct RenderObject
{

    virtual void render(SDL_Renderer *renderer) const= 0;
    glm::vec3 position;

    bool operator<(const RenderObject &other) const
    {
        return position.z < other.position.z;
    }
};

struct TextureRenderObject : public RenderObject
{
    SDL_Texture *texture = nullptr;
    SDL_FRect srcRect;
    SDL_FRect dstRect;
    void render(SDL_Renderer *renderer) const override
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
    }
};

struct RectangleRenderObject : public RenderObject
{
    SDL_FRect rect;
    SDL_Color color;

    void render(SDL_Renderer *renderer) const override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderRect(renderer, &rect);
    }
};
