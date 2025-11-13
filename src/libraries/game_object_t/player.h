#pragma once

#include "base_game_object.h"
#include <managers/material.h>
#include "component/component.h"

class Player : public GameObject
{
public:
    // Player-specific methods and attributes can be added here

    void init();

    void setDirection(float horizontal, float vertical);
    void update(float deltaTime);


    SDL_FRect getBoundingBox() const {
        glm::vec3 pos = getPosition();
        return SDL_FRect{pos.x, pos.y, size, size};
    }

    float getSize() const;

    const Material & getMaterial() const {
        return material;
    }

private:
    float speed = 200.0f;
    float size = 24.0f;
    glm::vec3 direction = glm::vec3(0.0f);
    Material material;
    RectangleCollider* collider = nullptr;
    SpriteComponent* sprite = nullptr;
};