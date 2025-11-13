#pragma once

#include "pch.h"

#include "material.h"
#include <game_object_t/game_object.h>

class RenderManager
{


public:


    void init();
    void destroy();
    
    void processEvent(SDL_Event* event);

    SDL_Texture *loadTexture(const char * filePath);

    void clear();
    void renderImGui();
    void present();
    void renderTexture(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *dstRect);
    
    void renderRectangle(const SDL_FRect &rect, const SDL_Color &color);
    void renderRectangle(float x, float y, float size, const SDL_Color &color);
    void resizeWindow(int width, int height);

    void setRenderScale();
    void convertEventScale(SDL_Event* event);
    void setLogicalPresentation(float logicalWidth, float logicalHeight);

    void renderMaterial(glm::vec3 position,const Material& material);
    void renderMaterial(glm::vec3 position,const Material* material);
    
    void renderGameObject(GameObject* object);

    void setCamera(glm::vec3 camera);

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void initWindow();
    void initRenderer();
    void initImGui();

    void destroyImGui();

    ImGuiIO* io = nullptr;
    
    glm::vec3 camera{0.0f,0.0f,0.0f};


    
};