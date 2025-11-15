#include "renderer.h"

namespace ts
{
    void Renderer::init()
    {
        // Initialize SDL video subsystem if not already done
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
        }

        // Create window
        window = SDL_CreateWindow(
            Config::WINDOW_NAME,
            windowWidth, windowHeight,
            Config::WINDOW_FLAGS);

        if (!window)
        {
            throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
        }

        initRenderer();

        // Set renderer blend mode for transparency
        SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
        setLogicalPresentation();

        if (Config::imGuiEnabled)
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            io = &ImGui::GetIO();
            (void)(*io);
            // Initialize ImGui for SDL3 and SDL Renderer
            ImGui_ImplSDL3_InitForSDLRenderer(window, sdlRenderer);
            ImGui_ImplSDLRenderer3_Init(sdlRenderer);
        }
    }

    void Renderer::destroy()
    {
        if (Config::imGuiEnabled)
        {
            // Cleanup ImGui
            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
        }
        // Clean up render objects
        for (auto *obj : renderObjects)
        {
            delete obj;
        }
        renderObjects.clear();

        // Clean up SDL resources
        if (sdlRenderer)
        {
            SDL_DestroyRenderer(sdlRenderer);
            sdlRenderer = nullptr;
        }

        if (window)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }

    void Renderer::newFrame()
    {
        // Clear render objects for next frame
        for (auto *obj : renderObjects)
        {
            delete obj;
        }
        renderObjects.clear();

        if (Config::imGuiEnabled)
        {
            // Start new ImGui frame
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
        }
        objectID = 0;

        renderReady = true;
    }

    void Renderer::setCamera(glm::vec2 cameraPosition, int cameraWidth, int cameraHeight)
    {

        camera.x = cameraPosition.x;
        camera.y = cameraPosition.y;
        camera.width = cameraWidth;
        camera.height = cameraHeight;
    }

    void Renderer::renderCommand()
    {
        if (!renderReady)
        {
            throw std::runtime_error("Renderer not ready. Call newFrame() before render().");
        }

        // Clear the screen
        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(sdlRenderer);

        // Render all objects (they're automatically sorted by z-depth due to std::set)
        for (const auto *obj : renderObjects)
        {
            Console::logFrame("Rendering object " + std::to_string(obj->objectID) + " at position (" + std::to_string(obj->position.x) + ", " + std::to_string(obj->position.y) + ", " + std::to_string(obj->position.z) + ")");

            if (obj)
            {
                obj->render(sdlRenderer);
            }
        }
    }

    void Renderer::render()
    {

        if (Config::imGuiEnabled)
        {
            // Render ImGui
            ImGui::Render();
            disableLogicalPresentation();
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), sdlRenderer);
            setLogicalPresentation();
        }

        // Present the rendered frame
        SDL_RenderPresent(sdlRenderer);
    }

    void Renderer::addTextureRenderObject(const SDL_Texture *texture, const SDL_FRect &srcRect, const SDL_FRect &dstRect, const glm::vec3 &position)
    {
        TextureRenderObject obj;
        obj.texture = const_cast<SDL_Texture *>(texture);
        obj.srcRect = srcRect;
        obj.dstRect = dstRect;
        obj.dstRect.x += position.x - static_cast<float>(camera.x);
        obj.dstRect.y += position.y - static_cast<float>(camera.y);
        obj.position = position;
        addRenderObject(new TextureRenderObject(obj));
    }

    void Renderer::addRectangleRenderObject(const SDL_FRect &rect, const SDL_Color &color, const glm::vec3 &position, bool filled)
    {
        RectangleRenderObject obj;
        obj.rect = rect;
        obj.rect.x += position.x - static_cast<float>(camera.x);
        obj.rect.y += position.y - static_cast<float>(camera.y);
        obj.color = color;
        obj.position = position;
        obj.filled = filled;
        addRenderObject(new RectangleRenderObject(obj));
    }

    SDL_Texture *Renderer::loadTexture(const std::string &filePath, int &width, int &height)
    {
        if (SDL_Surface *loadedSurface = IMG_Load(filePath.c_str()); loadedSurface == nullptr)
        {
            Console::log("Failed to load image: " + std::string(SDL_GetError()));
            return nullptr;
        }
        else
        {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, loadedSurface);
            width = loadedSurface->w;
            height = loadedSurface->h;
            if (texture == nullptr)
            {
                Console::log("Failed to create texture from surface: " + std::string(SDL_GetError()));
            }
            SDL_DestroySurface(loadedSurface);

            return texture;
        }
    }

    void Renderer::initRenderer()
    {
        // Try to create hardware accelerated renderer first
        sdlRenderer = SDL_CreateRenderer(window, Config::RENDERER_NAME);

        if (!sdlRenderer)
        {
            std::cerr << "Hardware accelerated renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            std::cerr << "Falling back to software renderer..." << std::endl;

            // Fallback to software renderer
            sdlRenderer = SDL_CreateRenderer(window, "software");
            if (!sdlRenderer)
            {
                std::cerr << "Software renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                throw std::runtime_error("Failed to create any SDL renderer");
            }
        }

        // Check renderer properties in SDL3
        const char *renderer_name = SDL_GetRendererName(sdlRenderer);
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

        SDL_SetRenderVSync(sdlRenderer, true);

        Console::log("Renderer initialized");
    }

    void Renderer::setLogicalPresentation()
    {
        SDL_SetRenderLogicalPresentation(sdlRenderer, logicalWidth, logicalHeight, Config::LOGICAL_PRESENTATION_FLAGS);
    }

    void Renderer::disableLogicalPresentation()
    {
        SDL_SetRenderLogicalPresentation(sdlRenderer, windowWidth, windowHeight, SDL_LOGICAL_PRESENTATION_DISABLED);
    }

    void Renderer::addRenderObject(RenderObject *obj)
    {
        obj->objectID = objectID++;
        renderObjects.insert(obj);
        Console::logFrame("Adding RenderObject " + std::to_string(obj->objectID) + " len of renderObjects " + std::to_string(renderObjects.size()));
    }
}