#pragma once

#include "player.h"
#include "camera.h"

// class Component;

// class GameObject
// {
// public:
//     template <class T, typename ... Args>
//     inline T* addComponent(Args&&... args)
//     {
//         // Placeholder for adding components
//         static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

//         auto component = std::make_unique<T>(std::forward<Args>(args)...);
//         component->assign(this);
//         T* componentPtr = component.get();
//         components.push_back(std::move(component));
//         return componentPtr;
//     }

//     template <class T>
//     inline bool hasComponent() const
//     {
//         for (const auto& comp : components)
//         {
//             if (dynamic_cast<T*>(comp.get()) != nullptr)
//             {
//                 return true;
//             }
//         }
//         return false;
//     }

//     template <class T>
//     inline T* getComponent() const
//     {
//         for (const auto& comp : components)
//         {
//             T* castedComp = dynamic_cast<T*>(comp.get());
//             if (castedComp != nullptr)
//             {
//                 return castedComp;
//             }
//         }
//         return nullptr;
//     }

// private:
//     std::vector<std::unique_ptr<Component>> components;
// };