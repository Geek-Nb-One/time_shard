#pragma once

#include "component.h"

namespace ts
{
    class Map : public Component
    {

    public:
        void init() override;
        void update(float deltaTime) override;
        void destroy() override;

        void load(int width, int height, int offsetX, int offsetY, int tileSize);
        int addTile(SDL_Texture *texture, const SDL_FRect &sourceRect);
        void setTile(int x, int y, int tileIndex);

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

        const Tile &getTileAt(int x, int y) const;

        GameManager &gameManager = GameManager::getInstance();
    };
}