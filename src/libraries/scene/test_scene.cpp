#include "test_scene.h"

namespace ts
{

    void TestScene::load(Renderer *renderer)
    {

        Console::log("Loading Test Scene");
        resourceManager.loadTexture(*renderer, "tiles", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\ground_cave_2x2_1.png");
        resourceManager.loadTexture(*renderer, "lili_down", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\lili_top_front.png");
        resourceManager.loadTexture(*renderer, "lili_up", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\lili_walk_back.png");
        resourceManager.loadTexture(*renderer, "lili_left", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\lili_walk_left.png");
        resourceManager.loadTexture(*renderer, "lili_right", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\lili_walk_right.png");
        auto camera = createCamera();
        camera->getComponent<CameraTracker>()->setFollowType(FollowType::SMOOTH);

        SDL_FRect srcRect = SDL_FRect{0, 0, 24, 24};
        SDL_FRect dstRect = SDL_FRect{-12, -12, 24, 24};

        GameObject *player = new GameObject();
        player->addComponent<Transform>();
        // player->addComponent<SpriteTexture>(resourceManager.getTexture("tiles")->sdlTexture, srcRect, dstRect);
        player->addComponent<SpriteTexture>();
        player->addComponent<PlayerController>();
        player->addComponent<Movement>();
        player->addComponent<StateMachinePlayer>();
        Animator *animator = player->addComponent<Animator>();


        auto addAnimation = [&](std::string textureName, std::string animationName)
        {
            Animation *animation = new Animation();

            animation->addFrame(resourceManager.getTexture(textureName)->sdlTexture, SDL_FRect{0, 0, 16, 32}, SDL_FRect{-8, -16, 16, 32}, 0.2f);
            animation->addFrame(resourceManager.getTexture(textureName)->sdlTexture, SDL_FRect{16, 0, 16, 32}, SDL_FRect{-8, -16, 16, 32}, 0.2f);
            animation->addFrame(resourceManager.getTexture(textureName)->sdlTexture, SDL_FRect{32, 0, 16, 32}, SDL_FRect{-8, -16, 16, 32}, 0.2f);
            animation->addFrame(resourceManager.getTexture(textureName)->sdlTexture, SDL_FRect{48, 0, 16, 32}, SDL_FRect{-8, -16, 16, 32}, 0.2f);
            animator->addAnimation(animationName, std::unique_ptr<Animation>(animation));
        };

        addAnimation("lili_up", "walk_up");
        addAnimation("lili_down","walk_down");
        addAnimation("lili_left","walk_left");
        addAnimation("lili_right","walk_right");

        Animation *idleAnimation = new Animation();
        idleAnimation->addFrame(resourceManager.getTexture("lili_down")->sdlTexture, SDL_FRect{0, 0, 16, 32}, SDL_FRect{-8, -16, 16, 32}, 0.2f);
        animator->addAnimation("idle", std::unique_ptr<Animation>(idleAnimation));
        

        player->tag = "Player";

        player->addComponent<Collider>();

        // player->addComponent<GameObjectTracker>();
        addGameObject(player);

        player->getComponent<Collider>()->setShapeBox(SDL_FRect{-12.0f, -12.0f, 24.0f, 24.0f});
        
        GameObject *npc = new GameObject();
        npc->addComponent<Transform>();
        npc->addComponent<SpriteCircle>(SDL_Color{0, 255, 255, 255}, 12, true);
        npc->addComponent<Collider>();
        addGameObject(npc);

        npc->getComponent<Collider>()->setShapeCircle(12.0f);
        npc->getComponent<Transform>()->position = glm::vec3(24.0f * 3, 0, 0.0f);
        camera->getComponent<CameraTracker>()->setTargetTransform(player->getComponent<Transform>());

        SDL_FRect srcDest[2] = {SDL_FRect{0, 0, 24, 24}, SDL_FRect{0, 24, 24, 24}};

        // for (int i = 0; i < 40;i++){
        //     for (int j = 0; j < 40 ;j++){
        //         int randomTileIndex = rand() % 2;

        //         GameObject* tile = new GameObject();
        //         tile->addComponent<Transform>();
        //         tile->addComponent<SpriteTexture>(resourceManager.getTexture("tiles")->sdlTexture, srcDest[randomTileIndex], SDL_FRect{-12.0f,-12.0f, 24.0f, 24.0f});
        //         addGameObject(tile);
        //         tile->init();
        //         tile->getComponent<Transform>()->position = glm::vec3(j * 24.0f-40/2*24, i * 24.0f-40/2*24, -1.0f);
        //     }
        // }

        GameObject *tile = new GameObject();
        tile->addComponent<Transform>();
        tile->addComponent<SpriteTexture>(resourceManager.getTexture("tiles")->sdlTexture, srcDest[0], SDL_FRect{-12.0f, -12.0f, 24.0f, 24.0f});
        tile->addComponent<Collider>();

        addGameObject(tile);
        tile->getComponent<Transform>()->position = glm::vec3(24 * 5, 24 * 5, -1.0f);
        tile->getComponent<Collider>()->setShapeBox(SDL_FRect{-12.0f, -12.0f, 24.0f, 24.0f});
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
