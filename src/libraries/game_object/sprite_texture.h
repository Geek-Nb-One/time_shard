#pragma once

#include "base_component.h"

namespace ts
{
    class SpriteTexture : public Component
    {

    public:

        SpriteTexture(SDL_Texture* texture = nullptr, const SDL_FRect& srcRect = SDL_FRect{0,0,0,0}, const SDL_FRect& dstRect = SDL_FRect{0,0,0,0});
        
        void init() override;

        void update(float deltaTime) override{};
        void destroy() override{};

        void setTexture(SDL_Texture *texture);
        SDL_Texture *getTexture() const;

        void setSourceRect(const SDL_FRect &rect);
        SDL_FRect getSourceRect() const;

        void setDestinationRect(const SDL_FRect &rect) ;
        SDL_FRect getDestinationRect() const;

        UpdatePriority getPriority() const override { return RENDER; }

    private:
        SDL_Texture *texture = nullptr;
        SDL_FRect srcRect{0, 0, 0, 0};
        SDL_FRect dstRect{0, 0, 0, 0};

    };
}