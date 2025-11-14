#pragma once

#include "../../pch.h"
#include "base_component.h"

namespace ts
{

    class GameObject
    {
    public:
        template <class T, typename... Args>
        T *addComponent(Args &&...args)
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
            auto component = std::make_unique<T>(std::forward<Args>(args)...);
            component->assign(this);
            T *componentPtr = component.get();
            components[typeid(T)] = std::move(component);
            return componentPtr;
        }

        template <class T>
        bool hasComponent() const
        {
            return components.find(typeid(T)) != components.end();
        }

        template <class T>
        T *getComponent() const
        {
            auto it = components.find(typeid(T));
            if (it != components.end())
            {
                return dynamic_cast<T *>(it->second.get());
            }
            return nullptr;
        }

        void init();
        void update(float deltaTime);
        void destroy();

    private:
        std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
        std::unique_ptr<GameObject> *parent = nullptr;
        std::vector<std::unique_ptr<GameObject>> children;
    };
}
