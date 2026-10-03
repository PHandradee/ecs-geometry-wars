#include "Entity.hpp"

int Entity::getEntityId() const { return m_entityId; };

void Entity::setEntityName(std::string_view name) {
    const auto& eManager{EntityManager::getInstance()};
    const auto e{eManager.getEntityByName(name)};
    std::string newName{name};
    if (e != nullptr) {
        newName.append("#" + std::to_string(m_entityId));
    }
    m_entityName = newName;
    return;
};

std::string_view Entity::getEntityName() const { return m_entityName; }

void Entity::setEntityTag(std::string tag) { m_entityTag = tag; }

std::string_view Entity::getEntityTag() const { return m_entityTag; }
