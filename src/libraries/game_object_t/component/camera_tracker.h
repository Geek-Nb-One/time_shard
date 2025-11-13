#pragma once


#include <managers/input_manager.h>
#include "../camera.h"
#include "../base_game_object.h"



class CameraTracker 
{
public:


    
    void update(float deltaTime);
    void setSpeed(float newSpeed);
    void trackObject(GameObject* object);

private:
    Camera * camera = nullptr;
    GameObject* trackedObject = nullptr;
    InputManager* input = InputManager::getInstance();
    float speed = 200.0f;
    bool enabled = true;
};
