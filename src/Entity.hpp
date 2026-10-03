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

    void setEntityName(std::string_view name);
    std::string_view getEntityName() const;

    void setEntityTag(std::string tag);
    std::string_view getEntityTag() const;

    template <typename T>
    T& addComponent();

    template <typename T>
    void removeComponent();

    template <typename T>
    T* getComponent();

    template <typename T>
    bool hasComponent();

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
T& Entity::addComponent() {
    auto& comp{std::get<T>(m_components)};
    comp.m_exists = true;
    return comp;
}

template <typename T>
void Entity::removeComponent() {
    auto& comp{std::get<T>(m_components)};
    comp.m_exists = false;
}

template <typename T>
T* Entity::getComponent() {
    auto& comp{std::get<T>(m_components)};
    if (comp.m_exists == true) {
        return &comp;
    }
    return nullptr;
}

template <typename T>
bool Entity::hasComponent() {
    auto& comp{std::get<T>(m_components)};
    return comp.m_exists;
};

#endif  // ENTITY_HPP
