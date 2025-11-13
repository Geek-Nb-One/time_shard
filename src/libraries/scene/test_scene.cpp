#include "test_scene.h"


#include <game_object_t/component/component.h>

void TestScene::load()
{

    // Load test scene resources

    loadMap();
    Camera* camera = addGameObject<Camera>();
    setMainCamera(camera);
    // camera->addComponent<CameraTracker>();
    
    // camera->setDimension(Config::LOGICAL_WIDTH, Config::LOGICAL_HEIGHT);

    // player = addGameObject<Player>();
    // player->init();

    // camera->getComponent<CameraTracker>()->trackObject(nullptr);

    Console::log("Player at " + std::to_string(player->getTransform().position.x) + ", " + std::to_string(player->getTransform().position.y));
}

void TestScene::unload()
{
    // Unload test scene resources
}



void TestScene::loadMap()
{

    // Render logic for TestState
    map.load(20, 15, 0, 0, 32);

    // Load Map
    auto filePath = "D:/Users/User/Documents/game_studio/projects/time_shard/assets/arts/ground_cave_2x2_1.png";
    SDL_Texture *texture = gameManager.renderer().loadTexture(filePath);

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
