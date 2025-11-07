#pragma once

#include "camera.h"


// Forward declaration
class GameObject;

class CameraTracker
{
public:
    CameraTracker(Camera* camera);
    
    void update(float deltaTime);
    void setSpeed(float newSpeed);

private:
    Camera* camera;
    GameObject* trackedObject = nullptr;
    float speed = 0.1f;
};
