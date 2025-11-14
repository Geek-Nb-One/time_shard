#include "camera.h"
#include "game_object.h"

namespace ts
{

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
    glm::vec2 Camera::getScreenPosition() const
    {

        return glm::vec2(transform->position.x - width / 2.0f, transform->position.y - height / 2.0f);
    }
}