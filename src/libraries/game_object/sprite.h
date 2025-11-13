#pragma once


#include "component.h"

class Sprite: Component{

public:
    void init() override;

    void setTexture(SDL_Texture* texture);
    SDL_Texture* getTexture() const;

    void setSourceRect(const SDL_FRect& rect);
    SDL_FRect getSourceRect() const;
};