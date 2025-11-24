#pragma once

#include "base_component.h"


namespace ts
{
    class SpriteCircle : public Component
    {
    public:
        SpriteCircle(const SDL_Color &color = SDL_Color{255, 255, 255, 255}, float radius = 0.0f, bool isFilled = false);

        SDL_Color getColor() const;
        float getRadius() const;

        void setColor(const SDL_Color &newColor);

        void setRadius(float newRadius);
        void setFilled(bool isFilled);
        bool isFilled() const ;
        UpdatePriority getPriority() const override { return RENDER; }
    private:
        SDL_Color color = SDL_Color{255, 255, 255, 255};
        float radius;
        bool filled = false;
    };
}