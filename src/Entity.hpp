#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <print>
#include <string>
#include <string_view>

#include "Component.hpp"
#include "EntityManager.hpp"

class Entity {
   public:
    auto getEntityId() const -> int;

    auto setEntityName(std::string_view name) -> void;
    auto getEntityName() const -> std::string_view;

    auto setEntityTag(std::string tag) -> void;
    auto getEntityTag() const -> std::string_view;

    template <typename T>
    auto addComponent() -> T&;

    template <typename T>
    auto removeComponent() -> void;

    template <typename T>
    auto getComponent() -> T*;

    template <typename T>
    auto hasComponent() -> bool;

    ~Entity() { std::println("Entity {} Destroyed", m_entityName); };

   private:
    int m_entityId{0};
    std::string m_entityName{};
    std::string m_entityTag{};
    ComponentContainer m_components{};

    Entity(const int entityId) : m_entityId(entityId) {};
    friend EntityManager;
};

template <typename T>
auto Entity::addComponent() -> T& {
    auto& comp{std::get<T>(m_components)};
    comp.m_exists = true;
    return comp;
}

template <typename T>
auto Entity::removeComponent() -> void {
    auto& comp{std::get<T>(m_components)};
    comp.m_exists = false;
}

template <typename T>
auto Entity::getComponent() -> T* {
    auto& comp{std::get<T>(m_components)};
    if (comp.m_exists == true) {
        return &comp;
    }
    return nullptr;
}

template <typename T>
auto Entity::hasComponent() -> bool {
    auto& comp{std::get<T>(m_components)};
    return comp.m_exists;
};

#endif  // ENTITY_HPP
