#pragma once

#include "pch.h"


struct Tile{
    SDL_Texture* texture;
    SDL_FRect srcRect;
};

namespace ts
{
    class MapLoader
    {

    public:
        MapLoader(int width, int height, int xOrigin, int yOrigin, int tileSize);
        void load(int width, int height, int xOrigin, int yOrigin, int tileSize);
        void unload();



    private:

        std::vector<SDL_Texture *> tileTextures;

    };
}