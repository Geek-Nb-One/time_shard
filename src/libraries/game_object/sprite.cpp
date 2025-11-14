#include "sprite.h"

ts::Sprite::Sprite(SDL_Texture *texture, const SDL_FRect &srcRect, const SDL_FRect &dstRect) : texture(texture), srcRect(srcRect), dstRect(dstRect) {}

void ts::Sprite::init()
{
}

void ts::Sprite::setTexture(SDL_Texture *texture)
{
}

SDL_Texture *ts::Sprite::getTexture() const
{
    return nullptr;
}

void ts::Sprite::setSourceRect(const SDL_FRect &rect)
{
}

SDL_FRect ts::Sprite::getSourceRect() const
{
    return SDL_FRect();
}

void ts::Sprite::setDestinationRect(const SDL_FRect &rect)
{
    dstRect = rect;
}

SDL_FRect ts::Sprite::getDestinationRect() const
{
    return dstRect;
}
