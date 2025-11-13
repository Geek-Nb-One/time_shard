#pragma once


#include "base_component.h"
#include "../base_game_object.h"
#include <manager/game_manager.h>

class PlayerController : public Component<GameObject>
{
public:
    PlayerController();
    void update(float deltaTime);
};