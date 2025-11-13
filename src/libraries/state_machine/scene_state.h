#pragma once

#include "state.h"
#include <scene/scene.h>

#include <scene/test_scene.h>

class SceneState : public State
{
public:
    void enter() override;
    void exit() override;
    void render() override;
    void update(float deltaTime) override;
    void handleEvent(const SDL_Event* event) override;

    void setScene(std::unique_ptr<Scene> newScene) {
        scene = std::move(newScene);
        sceneLoaded = false;
    }

private:
    std::unique_ptr<Scene> scene = nullptr;
    bool sceneLoaded = false;
};