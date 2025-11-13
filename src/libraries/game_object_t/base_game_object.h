#pragma once

#include "pch.h"
#include "component/component.h"





struct Transform
{
    glm::vec3 position{0.0f};
};

class GameObject
{

public:
    Transform &getTransform() { return transform; }

    glm::vec3 getPosition() const { return transform.position; }

    const Transform &getTransform() const { return transform; }

    void move(float deltaX, float deltaY, float deltaZ = 0.0f)
    {
        move(glm::vec3(deltaX, deltaY, deltaZ));
    }

    void move(const glm::vec3 &delta)
    {

        transform.position += delta;
    }

    template <class T, typename ... Args>
    inline T* addComponent(Args&&... args)
    {
        // Placeholder for adding components
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->assign(this);
        T* componentPtr = component.get();
        components.push_back(std::move(component));
        return componentPtr;
    }
    
    template <class T>
    bool hasComponent() const
    {
        for (const auto& comp : components)
        {
            if (dynamic_cast<T*>(comp.get()) != nullptr)
            {
                return true;
            }
        }
        return false;
    }


    template <class T>
    T* getComponent() const
    {
        for (const auto& comp : components)
        {
            if (auto ptr = dynamic_cast<T*>(comp.get()))
            {
                return ptr;
            }
        }
        return nullptr;
    }

private:
    Transform transform;
    std::vector<std::unique_ptr<Component>> components;
};