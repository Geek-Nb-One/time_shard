#pragma once

#include "scene.h"
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