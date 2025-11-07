#include "camera_tracker.h"

CameraTracker::CameraTracker(Camera* camera) : camera(camera) {
}

void CameraTracker::update(float deltaTime) {
    if (trackedObject) {
        glm::vec3 cameraPos = camera->getTransform().position;
        glm::vec3 targetPos = trackedObject->getTransform().position;

        glm::vec3 direction = glm::normalize(targetPos - cameraPos);
        camera->move(direction * speed * deltaTime);
    }
}

void CameraTracker::setSpeed(float newSpeed) {
    speed = newSpeed;
}