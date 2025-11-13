#include "sprite_component.h"

SpriteComponent::SpriteComponent(Material *material)
    : Component("SpriteComponent"), material(material)
{
}

Material* SpriteComponent::getMaterial() const
{
    return material;
}
