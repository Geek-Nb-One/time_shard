#include "test_scene.h"

namespace ts {

void TestScene::load(Renderer *renderer) {

    Console::log("Loading Test Scene");
    resourceManager.loadTexture(*renderer, "tiles", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\ground_cave_2x2_1.png");

    auto camera= createCamera();
    camera->getComponent<CameraTracker>()->setFollowType(FollowType::SMOOTH);    

    GameObject* player = new GameObject();
    player->addComponent<Transform>();

    SDL_FRect srcRect = SDL_FRect{0, 0 ,24,24};
    SDL_FRect dstRect = SDL_FRect{-12, -12, 24, 24};

    // player->addComponent<SpriteTexture>(resourceManager.getTexture("tiles")->sdlTexture, srcRect, dstRect);
    player->addComponent<SpriteColor>(SDL_Color{255, 0, 0, 255}, SDL_FRect{-12, -12, 24, 24}, true);
    player->addComponent<PlayerController>();
    player->addComponent<Movement>();
    player->tag = "Player";
    // player->addComponent<GameObjectTracker>();
    addGameObject(player);
    player->init();
    

    camera->getComponent<CameraTracker>()->setTargetTransform(player->getComponent<Transform>());

   

    GameObject * playerChild = new GameObject();
    playerChild->addComponent<Transform>();
    playerChild->addComponent<SpriteColor>(SDL_Color{0, 255, 0, 255}, SDL_FRect{-6, -6, 12, 12}, true);
    player->addChild(std::unique_ptr<GameObject>(playerChild));
    playerChild->init();
    playerChild->getComponent<Transform>()->position = glm::vec3(100.0f, 100.0f, 0.0f);
    

    SDL_FRect srcDest[2]= {SDL_FRect{0, 0 ,24,24}, SDL_FRect{0, 24 ,24,24}};

    for (int i = 0; i < 40;i++){
        for (int j = 0; j < 40 ;j++){
            int randomTileIndex = rand() % 2;

            GameObject* tile = new GameObject();
            tile->addComponent<Transform>();
            tile->addComponent<SpriteTexture>(resourceManager.getTexture("tiles")->sdlTexture, srcDest[randomTileIndex], SDL_FRect{-12.0f,-12.0f, 24.0f, 24.0f});
            addGameObject(tile);
            tile->init();
            tile->getComponent<Transform>()->position = glm::vec3(j * 24.0f-40/2*24, i * 24.0f-40/2*24, -1.0f);
        }
    }


    
}

void TestScene::unload() {
    // Unload test scene resources

    resourceManager.unload();

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
