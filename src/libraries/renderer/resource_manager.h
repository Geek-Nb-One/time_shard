#pragma once

#include "../../pch.h"

namespace ts
{

    class Renderer;

    struct TextureID
    {
        int id;
        bool operator==(const TextureID &other) const
        {
            return id == other.id;
        }
        bool operator!=(const TextureID &other) const
        {
            return id != other.id;
        }

        bool invalid = false;

        std::size_t hash() const
        {
            return std::hash<int>{}(id);
        }
        };
    }
    
    namespace std {
        template <>
        struct hash<ts::TextureID> {
            std::size_t operator()(const ts::TextureID& textureID) const {
                return textureID.hash();
            }
        };
    }
    
    namespace ts {
        struct Texture
    {
        std::string name;
        std::string path;
        SDL_Texture *sdlTexture = nullptr;
        TextureID id;
        int width;
        int height;
    };

    class ResourceManager
    {

    public:
        TextureID loadTexture(Renderer &renderer, const std::string &name, const std::string &path);
        Texture *getTexture(TextureID id);
        Texture *getTexture(const std::string &name);

        bool isValid(TextureID id) const;
        bool isValid(const std::string &name) const;

        void destroy();

    private:
        std::unordered_map<TextureID, std::unique_ptr<Texture>> textures;
        std::unordered_map<std::string, TextureID> nameToID;

        int nextTextureID = 0;
    };

#include "renderer.h"
};
