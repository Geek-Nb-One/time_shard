#pragma once

#include "../../pch.h"

namespace ts
{
    struct RenderObject
    {

        virtual void render(SDL_Renderer *renderer) const = 0;
        glm::i32vec3 position;
        int objectID;
    };

    struct TextureRenderObject : public RenderObject
    {
        SDL_Texture *texture = nullptr;
        SDL_FRect srcRect;
        int32_t x,y,w,h;
        void render(SDL_Renderer *renderer) const override
        {
            SDL_FRect dstRect;
            SDL_FRect adjustedSrcRect = srcRect;
            
            dstRect.x = static_cast<float>(x);
            dstRect.y = static_cast<float>(y);
            dstRect.w = static_cast<float>(w);
            dstRect.h = static_cast<float>(h);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderTexture(renderer, texture, &adjustedSrcRect, &dstRect);
        }
    };

    struct RectangleRenderObject : public RenderObject
    {
        uint32_t x,y,w,h;
        SDL_Color color;
        bool filled;

        void render(SDL_Renderer *renderer) const override
        {
            SDL_FRect dstRect;
            dstRect.x = static_cast<float>(x);
            dstRect.y = static_cast<float>(y);
            dstRect.w = static_cast<float>(w);
            dstRect.h = static_cast<float>(h);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            if (filled)
            {
                SDL_RenderFillRect(renderer, &dstRect);
            }
            else
            {
                SDL_RenderRect(renderer, &dstRect);
            }
        }
    };

}