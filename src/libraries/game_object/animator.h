#pragma once

#include "base_component.h"
#include "sprite_texture.h"

namespace ts
{

    class Animation{

    private:
        struct Frame
        {
            SDL_Texture* texture;
            SDL_FRect srcRect;
            SDL_FRect dstRect;
            float duration;
        };
        
        std::vector<Frame> frames;
        float frameTimer = 0.0f;
        int currentFrame = 0;
        bool isPlaying = false;
        bool loop = true;
        
    public:
        // Animation logic
        void play();
        void stop();
        void pause();
        void resume();
        
        void update(float deltaTime);
        
        // Data access
        const Frame& getCurrentFrame() const;
        bool isFinished() const;
        
        void addFrame(SDL_Texture* texture, const SDL_FRect& srcRect, 
                     const SDL_FRect& dstRect, float duration);
        
        void setLoop(bool shouldLoop);
        
    private:
        void nextFrame();
    };

    class Animator : public Component
    {
    private:
        SpriteTexture* spriteTexture = nullptr;
        std::unordered_map<std::string, std::unique_ptr<Animation>> animations;
        Animation* currentAnimation = nullptr;
        std::string currentAnimationName;
        
    public:
        void init() override;
        void update(float deltaTime) override;
        void destroy() override;
        
        // Animator manages animations (coordinator role)
        void addAnimation(const std::string& name, std::unique_ptr<Animation> animation);
        
        void playAnimation(const std::string& name,bool loop = true, bool forceRestart = false);
        
        void pauseAnimation();
        void resumeAnimation();
        void stopAnimation();
        
        Animation* getCurrentAnimation() const;
        const std::string& getCurrentAnimationName() const;
        
        UpdatePriority getPriority() const override { return ANIMATION; }
    };
}