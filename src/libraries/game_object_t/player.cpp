#include "player.h"

void Player::init()
{
    material.color = SDL_Color{255, 0, 0, 255}; // Red color
    material.offset =  glm::vec2(-size/2, -size/2);
    material.width = size;
    material.height = size;
    material.filled = false;

    collider = addComponent<RectangleCollider>(size, size);
    sprite = addComponent<SpriteComponent>(&material);
    
}

void Player::setDirection(float horizontal, float vertical)
{
    glm::vec3 inputDir(horizontal, vertical, 0.0f);
    float length = glm::length(inputDir);
    
    if (length > 0.0f) {
        direction = inputDir / length;  // Manual normalization
    } else {
        direction = glm::vec3(0.0f);    // Zero vector stays zero
    }
}

void Player::update(float deltaTime)
{

    glm::vec3 movement = direction * speed * deltaTime;
    move(movement);
}

float Player::getSize() const
{
    return size;
}
