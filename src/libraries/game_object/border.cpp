#include "border.h"

namespace ts
{
    Border::Border(const SDL_Color &color,const SDL_FRect &rect)
        : rect(rect), color(color)
    {
    }

    void Border::init()
    {
    }

    SDL_Color Border::getColor() const
    {
        return color;
    }
    SDL_FRect Border::getRect() const
    {
        return rect;
    }

    void Border::setColor(const SDL_Color &newColor)
    {
        color = newColor;
    }
    void Border::setRect(const SDL_FRect &newRect)
    {
        rect = newRect;
    }

}
