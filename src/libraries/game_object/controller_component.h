#pragma once

#include "base_component.h"

namespace ts
{
    class ControllerComponent : public Component
    {
    public:
        virtual void readInput() = 0;
    };
}