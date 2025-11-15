#include "renderer.h"
#include "resource_manager.h"

namespace ts
{


    TextureID ResourceManager::loadTexture(Renderer &renderer, const std::string &name, const std::string &path)
    {
           TextureID newTextureID{.id = nextTextureID++, .invalid = false};

        // Check if texture is already loaded
        for (const auto &pair : textures)
        {
            if (pair.second->name == name)
            {
                return pair.first;
            }
        }

        // Load texture using SDL_image
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (!surface)
        {
            // Handle error - could log or throw exception
            return TextureID{.invalid = true};
        }

        // Create SDL texture from surface
        int width, height;
        SDL_Texture *texture = renderer.loadTexture(path, width, height);

        if (!texture)
        {
            newTextureID.invalid = true;
            // Handle error
            return newTextureID;
        }

        textures.insert(std::make_pair(newTextureID, std::make_unique<Texture>(Texture{name, path, texture, newTextureID, width, height})));
        nameToID[name] = newTextureID;

        return newTextureID;

    }

    Texture *ResourceManager::getTexture(TextureID id)
    {
        auto it = textures.find(id);
        if (it != textures.end())
        {
            return it->second.get();
        }   
        return nullptr;
    }
    Texture *ResourceManager::getTexture(const std::string &name)
    {
        auto it = nameToID.find(name);
        if (it != nameToID.end())
        {
            return getTexture(it->second);
        }
        return nullptr;
    }
    bool ResourceManager::isValid(TextureID id) const
    {
        auto it = textures.find(id);
        return it != textures.end();
    }
    bool ResourceManager::isValid(const std::string &name) const
    {
        auto it = nameToID.find(name);
        if (it != nameToID.end())
        {
            return isValid(it->second);
        }   
        return false;
    }
    void ResourceManager::destroy()
    {
        for(auto& pair : textures){
            if(pair.second->sdlTexture){
                SDL_DestroyTexture(pair.second->sdlTexture);
                pair.second->sdlTexture = nullptr;
            }
        }
        textures.clear();
        nameToID.clear();
    }
} // namespace ts