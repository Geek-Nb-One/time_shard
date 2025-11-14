#include "component.h"

namespace ts
{

    void Component::assign(GameObject *gameObject)
    {
        this->gameObject = gameObject;
    }

    GameObject *Component::getGameObject() const
    {
        return gameObject;
    }
}
