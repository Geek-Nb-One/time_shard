#pragma once

#include "state.h"
#include <scene/scene.h>


#include <renderer/renderer.h>

namespace ts
{
    class SceneState : public State
    {
    public:
        SceneState(Scene* scene,Renderer *renderer);
        void enter() override;
        void exit() override;
        void render() override;
        void update(float deltaTime) override;
        void handleEvent(const SDL_Event *event) override;

      
    private:
        std::unique_ptr<Scene> scene = nullptr;
        bool sceneLoaded = false;
        ts::Renderer *renderer = nullptr;
    };
}