#include "Entity.hpp"

auto Entity::getEntityId() const -> int { return m_entityId; };

auto Entity::setEntityName(std::string_view name) -> void {
    const auto& eManager{EntityManager::getInstance()};
    const auto e{eManager.getEntityByName(name)};
    std::string newName{name};
    if (e != nullptr) {
        newName.append("#" + std::to_string(m_entityId));
    }
    m_entityName = newName;
    return;
};

auto Entity::getEntityName() const -> std::string_view { return m_entityName; }

auto Entity::setEntityTag(std::string tag) -> void { m_entityTag = tag; }

auto Entity::getEntityTag() const -> std::string_view { return m_entityTag; }
