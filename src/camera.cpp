#include "camera.h"

Point Camera::getScreenPosition(int x, int y) const {
    int screen_x = x - this->x;
    int screen_y = y - this->y;
    return Point(screen_x, screen_y);
}

void Camera::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Camera::getPosition(int &outX, int &outY) const {
    outX = x;
    outY = y;
}

void Camera::processEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN){
        switch (event.key.key){
            case SDLK_W:
                y -= 10;
                break;
            case SDLK_S:
                y += 10;
                break;
            case SDLK_A:
                x -= 10;
                break;
            case SDLK_D:
                x += 10;
                break;
        }
    }
}
