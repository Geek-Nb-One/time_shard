#include "render_manager.h"

void RenderManager::init()
{
    initWindow();
    initRenderer();

    setLogicalPresentation(Config::LOGICAL_WIDTH, Config::LOGICAL_HEIGHT);
    initImGui();
}

void RenderManager::destroy()
{
    destroyImGui();

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void RenderManager::processEvent(SDL_Event *event)
{
    if (event->type == SDL_EVENT_WINDOW_RESIZED)
    {
        resizeWindow(event->window.data1, event->window.data2);
    }
}

SDL_Texture *RenderManager::loadTexture(const char *filePath)
{

    SDL_Texture *texture = IMG_LoadTexture(renderer, filePath);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    return texture;
}

void RenderManager::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear with black color
    SDL_RenderClear(renderer);
}

void RenderManager::renderImGui()
{
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void RenderManager::present()
{
    SDL_RenderPresent(renderer);
}

void RenderManager::renderTexture(SDL_Texture *texture, const SDL_FRect *srcRect, const SDL_FRect *dstRect)
{
    SDL_RenderTexture(renderer, texture, srcRect, dstRect);
}

void RenderManager::renderRectangle(const SDL_FRect &rect, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(renderer, &rect);
}

void RenderManager::renderRectangle(float x, float y, float size, const SDL_Color &color)
{
    SDL_FRect rect = {x, y, size, size};
    renderRectangle(rect, color);
}

void RenderManager::resizeWindow(int width, int height)
{
    if (window)
    {
        SDL_SetWindowSize(window, width, height);
    }
}

void RenderManager::setRenderScale()
{
    SDL_SetRenderScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
}

void RenderManager::convertEventScale(SDL_Event *event)
{
    SDL_ConvertEventToRenderCoordinates(renderer, event);
}

void RenderManager::setLogicalPresentation(float logicalWidth, float logicalHeight)
{
    SDL_SetRenderLogicalPresentation(renderer, logicalWidth, logicalHeight, Config::LOGICAL_PRESENTATION_FLAGS);
}

void RenderManager::renderMaterial(glm::vec3 position, const Material &material)
{
    renderMaterial(position, &material);

}

void RenderManager::renderMaterial(glm::vec3 position, const Material *material)
{
    glm::vec2 adjustedLocation = material->offset + glm::vec2(position.x, position.y) - glm::vec2(camera.x, camera.y);
    SDL_FRect dstRect{
        adjustedLocation.x,
        adjustedLocation.y,
        material->width > 0.0f ? material->width : material->srcRect.w,
        material->height > 0.0f ? material->height : material->srcRect.h};

    SDL_SetRenderDrawColor(renderer, material->color.r, material->color.g, material->color.b, material->color.a);

    if (material->texture)
    {
        SDL_RenderTexture(renderer, material->texture, &material->srcRect, &dstRect);
    }
    else if (material->filled)
    {
        SDL_RenderFillRect(renderer, &dstRect);
    }
    else
    {
        SDL_RenderRect(renderer, &dstRect);
    }
}

void RenderManager::renderGameObject(GameObject *object)
{
    // if(object->hasComponent<SpriteComponent>())
    // {
    //     SpriteComponent* spriteComp = object->getComponent<SpriteComponent>();
    //     renderMaterial(object->getTransform().position, spriteComp->getMaterial());
    // }
}

void RenderManager::setCamera(glm::vec3 camera)
{
    this->camera = camera;
}

void RenderManager::initWindow()
{

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to initialize SDL");
    }

    // Create window
    window = SDL_CreateWindow(Config::WINDOW_NAME, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, Config::WINDOW_FLAGS);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL window");
    }
    
    Console::log("Window initialized");
}

void RenderManager::initRenderer()
{
    // Try to create hardware accelerated renderer first
    renderer = SDL_CreateRenderer(window, Config::RENDERER_NAME);

    if (!renderer)
    {
        std::cerr << "Hardware accelerated renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        std::cerr << "Falling back to software renderer..." << std::endl;

        // Fallback to software renderer
        renderer = SDL_CreateRenderer(window, "software");
        if (!renderer)
        {
            std::cerr << "Software renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            throw std::runtime_error("Failed to create any SDL renderer");
        }
    }

    // Check renderer properties in SDL3
    const char *renderer_name = SDL_GetRendererName(renderer);
    if (renderer_name)
    {
        Console::log(std::string("Using renderer: ") + renderer_name);

        // Check if it's a hardware accelerated renderer
        if (strcmp(renderer_name, "software") != 0)
        {
            Console::log("Hardware acceleration: LIKELY ENABLED");
        }
        else
        {
            Console::log("Hardware acceleration: DISABLED (using software)");
        }
    }

    SDL_SetRenderVSync(renderer, true);

    Console::log("Renderer initialized");
}

void RenderManager::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    (void)(*io);
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void RenderManager::destroyImGui()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
