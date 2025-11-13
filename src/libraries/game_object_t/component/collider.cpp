#include "collider.h"

#include "../base_game_object.h"

RectangleCollider::RectangleCollider(float width, float height) : ColliderComponent("RectangleCollider"), width(width), height(height)
{
}

bool RectangleCollider::checkCollision(RectangleCollider * other)
{
    glm::vec3 position = getGameObject()->getTransform().position;
    glm::vec3 otherPosition = other->getGameObject()->getTransform().position;
    // Simple AABB collision detection
    if (this->width <= 0 || this->height <= 0 || other->width <= 0 || other->height <= 0)
        return false; // No size means no collision

    // AABB collision detection using positions
    float left1 = position.x - this->width / 2.0f;
    float right1 = position.x + this->width / 2.0f;
    float top1 = position.y - this->height / 2.0f;
    float bottom1 = position.y + this->height / 2.0f;

    float left2 = otherPosition.x - other->width / 2.0f;
    float right2 = otherPosition.x + other->width / 2.0f;
    float top2 = otherPosition.y - other->height / 2.0f;
    float bottom2 = otherPosition.y + other->height / 2.0f;

    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2)
    {
        return true;
    }
return false;
}

void RectangleCollider::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
}