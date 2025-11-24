#pragma once

#include "scene.h"
#include <game_object/game_object.h>
#include <game_object/camera.h>
#include "../renderer/resource_manager.h"

namespace ts
{

    class TestScene : public Scene
    {
    public:
        void load(Renderer *renderer) override;

    private:
        // void loadMap();

        bool trackPlayer = true;


    };
}