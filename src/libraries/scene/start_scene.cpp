#include "start_scene.h"

void ts::StartScene::load(ts::Renderer *renderer)
{
    resourceManager.loadTexture(*renderer, "start_screen", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\splash_screen_base.bmp");

    GameObject *startScreen = new GameObject();
    startScreen->addComponent<Transform>();
    startScreen->addComponent<SpriteTexture>(resourceManager.getTexture("start_screen"), SDL_FRect{0, 0, 768, 432}, SDL_FRect{0, 0, 768, 432});
    addGameObject(startScreen);
    startScreen->init();
}