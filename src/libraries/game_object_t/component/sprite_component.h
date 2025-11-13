#pragma once

#include "base_component.h"
#include <managers/material.h>
#include "../base_game_object.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(Material * material);
    Material* getMaterial() const;
private:
    Material* material;
};