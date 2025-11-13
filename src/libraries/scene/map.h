#pragma once

#include "pch.h"

#include <game_object_t/camera.h>
#include <managers/game_manager.h>

struct Tile{
    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect;
};

class Map{

public:

    void load(int width, int height, int xOrigin, int yOrigin, int tileSize);
    void unload();

    int addTile(SDL_Texture* texture, SDL_FRect srcRect);
    void setTile(int x, int y, int textureIndex);

    void render(const Camera* camera);

private:
    std::vector<int> cells;
    std::vector<Tile> tiles;
    int width = 0;
    int height = 0;
    int xOrigin = 0;
    int yOrigin = 0;
    int tileSize = 24;
    int padding = 1;

    int getCellIndex(int x, int y) const;
    int getCellIndex(Point point) const;
    Point convertWorldToMap(int x, int y) const;
    Point convertWorldToMap(Point point) const;


    const Tile& getTileAt(int x, int y) const;

    GameManager& gameManager = GameManager::getInstance();

};