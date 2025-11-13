#pragma once


#include "scene.h"
#include "map.h"
#include <game_object_t/game_object.h>



class TestScene: public Scene{
public:
    void load() override;
    void unload() override;
    
private:

    GameManager& gameManager = GameManager::getInstance();
    
    void loadMap();

    bool trackPlayer = true;
    
};


