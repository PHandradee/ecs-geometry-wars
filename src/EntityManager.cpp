#include "EntityManager.hpp"

#include <algorithm>
#include <iterator>
#include <memory>
#include <ranges>

#include "Entity.hpp"

std::shared_ptr<Entity> EntityManager::createEntity() {
    ++m_entitiesCount;
    std::shared_ptr<Entity> entity{new Entity{m_entitiesCount}};
    m_entities.push_back(entity);
    return entity;
}

std::shared_ptr<Entity> EntityManager::createEntity(std::string_view name) {
    std::shared_ptr<Entity> entity{createEntity()};
    entity->m_entityName = name;
    return entity;
}

std::shared_ptr<Entity> EntityManager::getEntityById(const int entityId) const {
    auto entity{std::ranges::find_if(m_entities, [entityId](const auto& e) {
        return e->getEntityId() == entityId;
    })};
    if (entity == std::end(m_entities)) {
        return nullptr;
    }
    return *entity;
};