#pragma once

#include "base_game_object.h"

class Camera: public GameObject
{

public:

    glm::vec2 getScreenPosition(glm::vec3 position) const;
    glm::vec2 getScreenPosition(float x, float y, float z=0) const;

    int getWidth() const;
    int getHeight() const;

    void setDimension(int width, int height);

    glm::vec3 getCenter()const;

private:

    int width = 800;
    int height = 600;

};