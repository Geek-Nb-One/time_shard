#include "sprite_texture.h"

ts::SpriteTexture::SpriteTexture(SDL_Texture *texture, const SDL_FRect &srcRect, const SDL_FRect &dstRect) : texture(texture), srcRect(srcRect), dstRect(dstRect) {}

void ts::SpriteTexture::init()
{
}

void ts::SpriteTexture::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

SDL_Texture *ts::SpriteTexture::getTexture() const
{
    return texture;
}
void ts::SpriteTexture::setSourceRect(const SDL_FRect &rect)
{
    srcRect = rect;
}

SDL_FRect ts::SpriteTexture::getSourceRect() const
{
    return srcRect;
}


void ts::SpriteTexture::setDestinationRect(const SDL_FRect &rect)
{
    dstRect = rect;
}

SDL_FRect ts::SpriteTexture::getDestinationRect() const
{
    return dstRect;
}
