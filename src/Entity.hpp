#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <print>
#include <string>
#include <string_view>

#include "Component.hpp"
#include "EntityManager.hpp"

class Entity {
   public:
    int getEntityId() const;
    std::string_view getEntityName() const;

    void setEntityTag(std::string tag);
    std::string_view getEntityTag() const;

    template <typename T>
    T& addComponent(T& component);
    template <typename T>
    void removeComponent(T& component);
    template <typename T>
    T& getComponent() const;

    ~Entity() { std::println("Entity Destroyed"); };

   private:
    int m_entityId{};
    std::string m_entityName{};
    std::string m_entityTag{};
    ComponentContainer m_components{};

    Entity() = default;
    friend EntityManager;
};

#endif  // ENTITY_HPP
