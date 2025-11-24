#include "start_scene.h"

#include <managers/event_manager.h>

#include <game_object/game_object.h>
#include <game_object/camera.h>

void ts::StartScene::load(Renderer *renderer)
{
    resourceManager.loadTexture(*renderer, "start_screen", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\splash_screen_base.bmp");

    GameObject *UI = new GameObject();
    UI->addComponent<Transform>();
    UI->addComponent<SpriteTexture>(resourceManager.getTexture("start_screen")->sdlTexture, SDL_FRect{0, 0, 768, 432}, SDL_FRect{-768/2, -432/2, 768, 432});
    UI->addComponent<UiController>();
    addGameObject(UI);
    UI->init();

    createCamera();





}