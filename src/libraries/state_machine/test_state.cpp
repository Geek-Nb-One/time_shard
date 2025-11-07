#include "test_state.h"

#include <SDL3_image/SDL_image.h>

void TestState::enter()
{
    std::cout << "Entering TestState" << std::endl;
}

void TestState::handleEvent(const SDL_Event &event)
{
}

void TestState::update(float deltaTime)
{
   camera.move(getControlManager()->getHorizontalDirection() * CAMERA_SPEED , getControlManager()->getVerticalDirection() * CAMERA_SPEED );
}

void TestState::exit()
{
    std::cout << "Exiting TestState" << std::endl;
}

void TestState::init()
{
    // Render logic for TestState

    SDL_Renderer *renderer = getRenderer();


    camera.setDimension(768, 432);

    // Load Map
    SDL_Texture *texture = IMG_LoadTexture(renderer, "D:/Users/User/Documents/game_studio/projects/time_shard/assets/arts/ground_cave_2x2_1.png");
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    if (!texture)
    {
        throw std::runtime_error("Failed to load texture: " + std::string(SDL_GetError()));
    }

    std::vector<int> tiles;

    tiles.push_back(map.addTile(texture, SDL_FRect{0, 0, 24, 24}));
    tiles.push_back(map.addTile(texture, SDL_FRect{0, 24, 24, 24}));

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {

            int randomTileIndex = rand() % tiles.size();
            map.setTile(i, j, tiles[randomTileIndex]);
        }
    }
}

void TestState::render()
{

    SDL_Renderer *renderer = getRenderer();

    SDL_RenderClear(renderer);
    map.draw(renderer, camera);
    SDL_RenderPresent(renderer);
}