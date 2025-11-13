#include "component.h"

#include "../base_game_object.h"
#include "base_component.h"


Component::Component(const char *name) :name(name)
{
}
void Component::assign(GameObject *owner)
{
    this->gameObject = owner;
}
const char* Component::getName() const
{
    return name;
}
GameObject *Component::getGameObject() const
{
    return gameObject;
}

Transform &Component::getTransform() const
{
    // TODO: insert return statement here
    return gameObject->getTransform();
}
