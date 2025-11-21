#pragma once

#include "../../pch.h"
#include "render_object.h"
#include "resource_manager.h"

namespace ts
{
    struct RenderCamera
    {
        float x, y, width, height;
    };

    class Renderer
    {

    public:
        void init();
        void destroy();

        void newFrame();
        void setCamera(glm::vec2 cameraPosition, int cameraWidth, int cameraHeight);

        void renderCommand();
        void render();

        void addTextureRenderObject(const SDL_Texture *texture, const SDL_FRect &srcRect, const SDL_FRect &dstRect, const glm::vec3 &position);
        void addRectangleRenderObject(const SDL_FRect &rect, const SDL_Color &color, const glm::vec3 &position, bool filled);
        
        SDL_Texture* loadTexture(const std::string &filePath,int& width, int& height);
        
    private:
        struct RenderObjectComparator
        {
            bool operator()(const RenderObject *a, const RenderObject *b) const
            {
                if (a->position.z == b->position.z)
                {
                    return a->objectID < b->objectID;
                }
                return a->position.z < b->position.z; // Sort by z-depth
            };
        };
        std::set<RenderObject *, RenderObjectComparator> renderObjects;
        int objectID = 0;

        SDL_Window *window = nullptr;
        SDL_Renderer *sdlRenderer = nullptr;

        RenderCamera camera{.x = 0, .y = 0, .width = Config::LOGICAL_WIDTH, .height = Config::LOGICAL_HEIGHT};

        void initRenderer();
        bool renderReady = false;

        ImGuiIO *io = nullptr;

        void setLogicalPresentation();
        void disableLogicalPresentation();

        int windowWidth = Config::WINDOW_WIDTH;
        int windowHeight = Config::WINDOW_HEIGHT;
        int logicalWidth = Config::LOGICAL_WIDTH;
        int logicalHeight = Config::LOGICAL_HEIGHT;

        void addRenderObject(RenderObject *obj);
    };
}