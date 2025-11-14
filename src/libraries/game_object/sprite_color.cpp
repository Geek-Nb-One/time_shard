#include "sprite_color.h"

namespace ts
{
    SpriteColor::SpriteColor(const SDL_Color &color, const SDL_FRect &rect, bool isFilled)
        : rect(rect), color(color), filled(isFilled)
    {
    }

    void SpriteColor::init()
    {
    }

    SDL_Color SpriteColor::getColor() const
    {
        return color;
    }
    SDL_FRect SpriteColor::getRect() const
    {
        return rect;
    }

    void SpriteColor::setColor(const SDL_Color &newColor)
    {
        color = newColor;
    }
    void SpriteColor::setRect(const SDL_FRect &newRect)
    {
        rect = newRect;
    }
    void SpriteColor::setFilled(bool isFilled)
    {
        filled = isFilled;
    }
    bool SpriteColor::isFilled() const
    {
        return filled;
    }

}
