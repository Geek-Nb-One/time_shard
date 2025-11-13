#include "camera_tracker.h"




void CameraTracker::update(float deltaTime)
{
    if(input->isActive(CAMERA_ATTACH_TOGGLE))
    {
        enabled = !enabled;
    }

    if (enabled && trackedObject)
    {
        
        glm::vec3 cameraPos = camera->getCenter();
        glm::vec3 targetPos = trackedObject->getTransform().position;
        
        glm::vec3 direction = targetPos - cameraPos;

    

        float len = glm::length(direction);
        glm::vec3 normalizedDir = direction;
        if (len > 0.0f) {
            normalizedDir /= len; // Normalize
        } else {
            normalizedDir = glm::vec3(0.0f); // No movement needed
        }
        
        glm::vec3 velocity = normalizedDir * speed * deltaTime;
        float velocityLength = glm::length(velocity);
        
        if(velocityLength > len)
        {
            camera->move(direction);
        }else{
            camera->move(velocity);
        }
    }
}

void CameraTracker::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

void CameraTracker::trackObject(GameObject *object)
{
    trackedObject = object;
}
