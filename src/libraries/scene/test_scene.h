#pragma once

#include "scene.h"
#include <game_object/game_object.h>
#include <game_object/camera.h>

namespace ts
{

    class TestScene : public Scene
    {
    public:
        void load() override;
        void unload() override;

    private:
        // void loadMap();

        bool trackPlayer = true;
    };
}