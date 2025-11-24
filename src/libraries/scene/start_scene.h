#pragma once

#include "scene.h"

namespace ts
{

    class StartScene : public Scene
    {

    public:
        void load(Renderer *renderer) override;

    };
}