#include "animator.h"

namespace ts
{
    // Animation class implementations
    void Animation::play() {
        isPlaying = true;
        frameTimer = 0.0f;
    }

    void Animation::stop() {
        isPlaying = false;
        currentFrame = 0;
        frameTimer = 0.0f;
    }

    void Animation::pause() {
        isPlaying = false;
    }

    void Animation::resume() {
        isPlaying = true;
    }

    void Animation::update(float deltaTime) {
        if (!isPlaying || frames.empty()) return;
        
        frameTimer += deltaTime;
        if (frameTimer >= frames[currentFrame].duration) {
            frameTimer = 0.0f;
            nextFrame();
        }
    }

    const Animation::Frame& Animation::getCurrentFrame() const {
        static Frame emptyFrame{};
        return frames.empty() ? emptyFrame : frames[currentFrame];
    }

    bool Animation::isFinished() const {
        return !isPlaying && !loop && currentFrame >= frames.size() - 1;
    }

    void Animation::addFrame(SDL_Texture* texture, const SDL_FRect& srcRect, 
                            const SDL_FRect& dstRect, float duration) {
        frames.push_back({texture, srcRect, dstRect, duration});
    }

    void Animation::setLoop(bool shouldLoop) {
        loop = shouldLoop;
    }

    void Animation::nextFrame() {
        currentFrame++;
        if (currentFrame >= frames.size()) {
            if (loop) {
                currentFrame = 0;
            } else {
                currentFrame = frames.size() - 1;
                isPlaying = false;
            }
        }
    }

    // Animator class implementations
    void Animator::init() {
        spriteTexture = getGameObject()->getComponent<SpriteTexture>();
    }

    void Animator::update(float deltaTime) {
        if (currentAnimation) {
            currentAnimation->update(deltaTime);
            
            // Update sprite texture with current frame
            if (spriteTexture) {
                const auto& frame = currentAnimation->getCurrentFrame();
                if (frame.texture) {
                    spriteTexture->setTexture(frame.texture);
                    spriteTexture->setSourceRect(frame.srcRect);
                    spriteTexture->setDestinationRect(frame.dstRect);
                }
            }
        }
    }

    void Animator::destroy() {
        stopAnimation();
        animations.clear();
    }

    void Animator::addAnimation(const std::string& name, std::unique_ptr<Animation> animation) {
        animations[name] = std::move(animation);
    }

    void Animator::playAnimation(const std::string &name, bool loop, bool forceRestart)
    {
        auto it = animations.find(name);
        if (it != animations.end()) {
            if (currentAnimationName != name || forceRestart) {
                if (currentAnimation) currentAnimation->stop();
                
                currentAnimation = it->second.get();
                currentAnimationName = name;
                currentAnimation->setLoop(loop);
                currentAnimation->play();
            }
        }
    }



    void Animator::pauseAnimation() {
        if (currentAnimation) currentAnimation->pause();
    }

    void Animator::resumeAnimation() {
        if (currentAnimation) currentAnimation->resume();
    }

    void Animator::stopAnimation() {
        if (currentAnimation) {
            currentAnimation->stop();
            currentAnimation = nullptr;
            currentAnimationName.clear();
        }
    }

    Animation* Animator::getCurrentAnimation() const {
        return currentAnimation;
    }

    const std::string& Animator::getCurrentAnimationName() const {
        return currentAnimationName;
    }
}