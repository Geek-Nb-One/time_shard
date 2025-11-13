#include "camera.h"
#include "game_object.h"

namespace ts
{
    glm::vec2 Camera::getScreenPosition(glm::vec3 position) const
    {
        glm::vec2 screenPosition;
        screenPosition.x = position.x - transform->position.x;
        screenPosition.y = position.y - transform->position.y;
        return screenPosition;
    }

    glm::vec2 Camera::getScreenPosition(float x, float y, float z) const
    {
        return getScreenPosition(glm::vec3(x, y, z));
    }

    int Camera::getWidth() const { return width; }
    int Camera::getHeight() const { return height; }

    void Camera::setDimension(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    glm::vec3 Camera::getCenter() const
    {
        return transform->position + glm::vec3(width / 2.0f, height / 2.0f, 0.0f);
    }

    void Camera::init()
    {
        width = 800;
        height = 600;
        transform = getGameObject()->getComponent<Transform>();
        Console::log("Camera initialized with width: " + std::to_string(width) + " height: " + std::to_string(height));
    }
}