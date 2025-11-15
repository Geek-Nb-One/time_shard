#include "sprite_group.h"


namespace ts
{


    float SpriteGroup::getWidth() const
    {
        return width;
    }

    float SpriteGroup::getHeight() const
    {
        return height;
    }


    void SpriteGroup::setWidth(float w)
    {
        width = w;
    }

    void SpriteGroup::setHeight(float h)
    {
        height = h;
    }

    void SpriteGroup::init()
    {
        transform = getGameObject()->getComponent<Transform>();
    }

    bool SpriteGroup::inCameraView(const glm::vec2 &cameraPos, int cameraWidth, int cameraHeight) const
    {
        float spriteRight = transform->position.x + width;
        float spriteBottom = transform->position.y + height;
        float cameraRight = cameraPos.x + cameraWidth;
        float cameraBottom = cameraPos.y + cameraHeight;

        return !(spriteRight < cameraPos.x || transform->position.x > cameraRight ||
                 spriteBottom < cameraPos.y || transform->position.y > cameraBottom);
    }
}