#pragma once


#include "state.h"
#include <scene/scene.h>
#include <renderer/renderer.h>

namespace ts{

    class LoadingState : public State{
    public:

        LoadingState(Scene* scene, Renderer* renderer);
        void enter() override;
        void update(float deltaTime) override;
        void render() override;
        void handleEvent(const SDL_Event* event) override{}
        void exit() override;

    private:
        float loadProgress = 0.0f;
        bool isLoaded = false;

        Scene *scene = nullptr;
        Renderer* renderer = nullptr;

    };
}