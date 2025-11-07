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

void Camera::processEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch (event.key.key)
        {
        case SDLK_W:
            getTransform().position.y -= 10;
            break;
        case SDLK_S:
            getTransform().position.y += 10;
            break;
        case SDLK_A:
            getTransform().position.x -= 10;
            break;
        case SDLK_D:
            getTransform().position.x += 10;
            break;
        }
    }
}


int Camera::getWidth() const { return width; }
int Camera::getHeight() const { return height; }

void Camera::setDimension(int width, int height)
{
    this->width = width;
    this->height = height;
}
