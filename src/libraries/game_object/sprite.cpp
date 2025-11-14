#include "sprite.h"

ts::Sprite::Sprite(SDL_Texture *texture, const SDL_FRect &srcRect, const SDL_FRect &dstRect) : texture(texture), srcRect(srcRect), dstRect(dstRect) {}

void ts::Sprite::init()
{
}

void ts::Sprite::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

SDL_Texture *ts::Sprite::getTexture() const
{
    return texture;
}
void ts::Sprite::setSourceRect(const SDL_FRect &rect)
{
    srcRect = rect;
}

SDL_FRect ts::Sprite::getSourceRect() const
{
    return srcRect;
}


void ts::Sprite::setDestinationRect(const SDL_FRect &rect)
{
    dstRect = rect;
}

SDL_FRect ts::Sprite::getDestinationRect() const
{
    return dstRect;
}
