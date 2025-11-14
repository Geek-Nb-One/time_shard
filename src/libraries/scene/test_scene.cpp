#include "test_scene.h"

namespace ts {

void TestScene::load() {
    GameObject* camera = new GameObject();
    camera->addComponent<Transform>();
    camera->addComponent<Camera>();
    addGameObject(camera);
    setMainCamera(camera);
    camera->init();

    GameObject* player = new GameObject();
    player->addComponent<Transform>();
    player->addComponent<Border>(SDL_Color{255, 0, 0, 255}, SDL_FRect{-25, -25, 50, 50});
    addGameObject(player);
    player->init();
}

void TestScene::unload() {
    // Unload test scene resources
}

} // namespace ts


// void TestScene::loadMap()
// {

//     // Render logic for TestState
//     map.load(20, 15, 0, 0, 32);

//     // Load Map
//     auto filePath = "D:/Users/User/Documents/game_studio/projects/time_shard/assets/arts/ground_cave_2x2_1.png";
//     SDL_Texture *texture = gameManager.renderer().loadTexture(filePath);

//     if (!texture)
//     {
//         throw std::runtime_error("Failed to load texture: " + std::string(SDL_GetError()));
//     }

//     std::vector<int> tiles;

//     tiles.push_back(map.addTile(texture, SDL_FRect{0, 0, 24, 24}));
//     tiles.push_back(map.addTile(texture, SDL_FRect{0, 24, 24, 24}));

//     for (int i = 0; i < 10; ++i)
//     {
//         for (int j = 0; j < 10; ++j)
//         {

//             int randomTileIndex = rand() % tiles.size();
//             map.setTile(i, j, tiles[randomTileIndex]);
//         }
//     }
// }
