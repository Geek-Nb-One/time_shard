#pragma once

#include "pch.h"

#include "../renderer/resource_manager.h"

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
        void load(ResourceManager* resourceManager);
        void unload();



    private:
        int width;
        int height;
        int xOrigin;
        int yOrigin;
        int tileSize;

        std::vector<std::vector<Tile>> tiles;


    };
}