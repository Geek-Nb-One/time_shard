#pragma once


#include "base_component.h"
#include "transform.h"

namespace ts {
    class Movement : public Component {

        
    public:
        void update(float deltaTime) override;
        void moveBack();
        // void applyMove();

        void move(const glm::vec3& dir);
        void stop();
        void setSpeed(float newSpeed);

        bool isMoving() const;

        Direction getDirection() const; 

        UpdatePriority getPriority() const override { return MOVEMENT; }

    private:
        glm::vec3 direction{0, 0, 0};
        float speed = 100.0f;
        bool _isMoving = false;
    };
}