#include "camera.h"


glm::vec2 Camera::getScreenPosition(glm::vec3 position) const
{
    glm::vec2 screenPosition;
    screenPosition.x = position.x - getTransform().position.x;
    screenPosition.y = position.y - getTransform().position.y;
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
    return getTransform().position + glm::vec3(width / 2.0f, height / 2.0f, 0.0f);
}


