#pragma once

#include "../../pch.h"

struct RenderObject
{

    virtual void render(SDL_Renderer *renderer) const = 0;
    glm::vec3 position;
    int objectID;


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
    bool filled;

    void render(SDL_Renderer *renderer) const override
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        if (filled)
        {
            SDL_RenderFillRect(renderer, &rect);
        }
        else
        {
            SDL_RenderRect(renderer, &rect);
        }
    }
};
