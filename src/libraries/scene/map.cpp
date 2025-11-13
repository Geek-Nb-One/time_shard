#include "map.h"



void Map::load(int width, int height, int xOrigin, int yOrigin, int tileSize)
{
    this->width = width;
    this->height = height;
    this->xOrigin = xOrigin;
    this->yOrigin = yOrigin;
    this->tileSize = tileSize;
    cells.resize(width * height, 0);
    tiles.push_back({nullptr, {0, 0, 0, 0}}); // Index 0 reserved for no texture
}

void Map::unload()
{
    cells.clear();
    tiles.clear();
}

int Map::addTile(SDL_Texture* texture, SDL_FRect srcRect)
{
    Tile newTile;
    newTile.texture = texture;
    newTile.srcRect = srcRect;
    tiles.push_back(newTile);
    return tiles.size() - 1; // Return the index of the added tile   
}

void Map::setTile(int x, int y, int textureIndex)
{
    int cellIndex = getCellIndex(x, y);
    if (cellIndex >= 0 && cellIndex < cells.size())
    {
        cells[cellIndex] = textureIndex;
    }
}

void Map::render(const Camera *camera)
{

    // int cameraX, cameraY;
    // auto cameraPosition = camera->getTransform().position;
    // int xOffset = camera->getWidth() / tileSize + padding * 2;
    // int yOffset = camera->getHeight() / tileSize + padding * 2;

    // int ix = std::floor((cameraPosition.x + xOrigin) / static_cast<float>(tileSize)) - padding;
    // int iy = std::floor((cameraPosition.y + yOrigin) / static_cast<float>(tileSize)) - padding;

    // for (int x = ix; x < xOffset + ix; ++x)
    // {
    //     for (int y = iy; y < yOffset + iy; ++y)
    //     {

    //         int worldX = x * tileSize + xOrigin;
    //         int worldY = y * tileSize + yOrigin;
    //         const Tile& tile = getTileAt(x, y);

    //         if (tile.texture == nullptr)
    //         {
    //             continue; // Skip drawing if there's no texture
    //         }
    //         auto screenPosition = camera->getScreenPosition(worldX, worldY,0);

    //         SDL_FRect destRect{
    //             static_cast<float>(screenPosition.x),
    //             static_cast<float>(screenPosition.y),
    //             static_cast<float>(tileSize),
    //             static_cast<float>(tileSize)};
    //         gameManager.renderer().renderTexture(tile.texture, &tile.srcRect, &destRect);
    //     }
    // }
}

int Map::getCellIndex(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return -1; // Out of bounds
    }
    return y * width + x;
}

int Map::getCellIndex(Point point) const
{
    return getCellIndex(point.first, point.second);
}

Point Map::convertWorldToMap(int x, int y) const
{
    return Point((int)((x - xOrigin) / tileSize), (int)((y - yOrigin) / tileSize));
}

Point Map::convertWorldToMap(Point point) const
{
    return convertWorldToMap(point.first, point.second);
}

const Tile& Map::getTileAt(int x, int y) const
{
    int cellIndex = getCellIndex(x, y);
    if (cellIndex >= 0 && cellIndex < cells.size())
    {
        int tileIndex = cells[cellIndex];

        return tiles.at(tileIndex);
    }
    return tiles.at(0); // Return a default empty tile if out of bounds
}
