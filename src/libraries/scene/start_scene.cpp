#include "start_scene.h"

#include <managers/event_manager.h>

#include <game_object/game_object.h>
#include <game_object/camera.h>
#include <managers/audio_manager.h>

namespace ts
{
    // Define any StartScene-specific methods or members here

    void StartScene::load(Renderer *renderer)
    {
        resourceManager.loadTexture(*renderer, "start_screen", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\arts\\splash_screen_base.bmp");

        GameObject *UI = new GameObject();
        UI->addComponent<Transform>();
        UI->addComponent<SpriteTexture>(resourceManager.getTexture("start_screen")->sdlTexture, SDL_FRect{0, 0, 768, 432}, SDL_FRect{-768 / 2, -432 / 2, 768, 432});
        UI->addComponent<UiController>();
        addGameObject(UI);
        UI->init();

        createCamera();

        AudioManager *audio = AudioManager::getInstance();

        audio->loadAudio("start_music", "D:\\Users\\User\\Documents\\game_studio\\projects\\time_shard\\assets\\audio\\sample_mp3.mp3");
        audio->startTrack("music","start_music", true);
    
    }
}