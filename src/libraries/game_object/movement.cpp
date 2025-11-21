#include "movement.h"

namespace ts {
    void Movement::update(float deltaTime) {
        if (isMoving) {
            Transform* transform = getGameObject()->getComponent<Transform>();
            if (transform) {
                transform->position += direction * speed * deltaTime;
            }
        }
    }
    void Movement::move(const glm::vec3& dir) {
        direction = glm::normalize(dir);
        isMoving = true;
    }
    void Movement::stop() {
        isMoving = false;
        direction = glm::vec3(0, 0, 0);
    }
    void Movement::setSpeed(float newSpeed) {
        speed = newSpeed;
    }

}