#include "sprite_circle.h"


namespace ts
{
    SpriteCircle::SpriteCircle(const SDL_Color &color, float radius, bool isFilled)
        : radius(radius), color(color), filled(isFilled)
    {
    }   
    SDL_Color SpriteCircle::getColor() const
    {
        return color;
    }
    float SpriteCircle::getRadius() const
    {
        return radius;
    }
    void SpriteCircle::setColor(const SDL_Color &newColor)
    {
        color = newColor;
    }
    void SpriteCircle::setRadius(float newRadius)
    {
        radius = newRadius;
    }
    void SpriteCircle::setFilled(bool isFilled)
    {
        filled = isFilled;
    }
    bool SpriteCircle::isFilled() const
    {
        return filled;
    }
}   