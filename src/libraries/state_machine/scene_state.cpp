#include "scene_state.h"

void SceneState::enter()
{
    
    Console::log("Entering SceneState");
    if(!sceneLoaded && scene == nullptr){
        scene = std::make_unique<ts::TestScene>();
        scene->load();
        sceneLoaded = true;
        Console::log("Scene loaded in SceneState");
    }
}

void SceneState::exit()
{   
    if(sceneLoaded && scene){
        scene->unload();
        sceneLoaded = false;
    }
}

void SceneState::render(Renderer& renderer)
{
    if(scene && sceneLoaded){
        scene->render(renderer);
    }
}

void SceneState::update(float deltaTime)
{
    if(scene && sceneLoaded){
        scene->update(deltaTime);
    }
}

void SceneState::handleEvent(const SDL_Event *event)
{

}
