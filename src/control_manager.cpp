#include "control_manager.h"

void ControlManager::processInput(const SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        processKey(event->key.key, true);
    }
    else if (event->type == SDL_EVENT_KEY_UP)
    {
        processKey(event->key.key, false);
    }
}

int ControlManager::getHorizontalDirection() const
{
    int direction = 0;
    if (keyPressed & (1 << LEFT)) direction -= 1;
    if (keyPressed & (1 << RIGHT)) direction += 1;
    return direction;
}

int ControlManager::getVerticalDirection() const
{
    int direction = 0;
    if (keyPressed & (1 << DOWN)) direction += 1;
    if (keyPressed & (1 << UP)) direction -= 1;
    return direction;
}

void ControlManager::processKey(SDL_Keycode key, bool pressed)
{
    int keyControlCode = 0;
    switch(key){
        case SDLK_A:
        case SDLK_LEFT:
            keyControlCode = LEFT;
            break;
        case SDLK_D:
        case SDLK_RIGHT:
            keyControlCode = RIGHT;
            break;
        case SDLK_W:
        case SDLK_UP:
            keyControlCode = UP;
            break;
        case SDLK_S:
        case SDLK_DOWN:
            keyControlCode = DOWN;
            break;
        default:
            return;
    }
    if (pressed) {
        keyPressed |= (1 << keyControlCode);
    } else {
        keyPressed &= ~(1 << keyControlCode);
    }
}
