#pragma once

#include "base_component.h"

namespace ts
{
    class Border : public Component
    {
    public:
        Border(const SDL_Color &color = SDL_Color{255, 255, 255, 255}, const SDL_FRect &rect = SDL_FRect{0, 0, 0, 0});
        void init() override;
        void update(float deltaTime) override {};
        void destroy() override {};

        SDL_Color getColor() const;
        SDL_FRect getRect() const;

        void setColor(const SDL_Color &newColor);

        void setRect(const SDL_FRect &newRect);

    private:
        SDL_Color color = SDL_Color{255, 255, 255, 255};
        SDL_FRect rect;
    };
}