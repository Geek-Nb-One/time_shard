#include "map_loader.h"

namespace ts{
    MapLoader::MapLoader(int width, int height, int xOrigin, int yOrigin, int tileSize):
    width(width), height(height), xOrigin(xOrigin), yOrigin(yOrigin), tileSize(tileSize)
    {

    }
    void MapLoader::load(ResourceManager *resourceManager)
    {
    }
    void MapLoader::unload()
    {
    }
}