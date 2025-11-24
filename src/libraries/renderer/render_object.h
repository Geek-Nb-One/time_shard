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
        int32_t x, y, w, h;
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
        int32_t x, y, w, h;
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

    struct CircleRenderObject : public RenderObject
    {
        int32_t x, y;
        float radius;
        SDL_Color color;
        bool filled;

        void render(SDL_Renderer *renderer) const override
        {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            std::vector<SDL_FPoint> points;
            for (int i = -radius; i <= radius; i++)
            {
                for (int j = -radius; j <= radius; j++)
                {
                    if (i * i + j * j <= radius * radius)
                    {
                        points.push_back({static_cast<float>(x + i), static_cast<float>(y + j)});
                    }
                }
            }
            SDL_RenderPoints(renderer, points.data(), points.size());
        }
    };

}