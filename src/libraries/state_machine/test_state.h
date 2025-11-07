#pragma once

#include "../pch.h"
#include "state.h"
#include <game_object/camera.h>
#include "../../control_manager.h"
#include "../../map.h"
#include <game_object/camera_tracker.h>


class TestState : public State
{
public:

    void enter() override;

    void update(float deltaTime) override;

    void render() override;

    void handleEvent(const SDL_Event &event) override;

    void exit() override;

    void init() override;

private:
    // Add any private members or methods for TestState

    Camera camera;
    Map map{10, 10, 0, 0, 24};

    const int CAMERA_SPEED = 5;
};