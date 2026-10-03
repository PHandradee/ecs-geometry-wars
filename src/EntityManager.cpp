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
    entity->setEntityName(name);
    return entity;
}

std::shared_ptr<Entity> EntityManager::getEntityById(const int entityId) const {
    auto entity{std::ranges::find_if(m_entities, [entityId](const auto& e) {
        return e->getEntityId() == entityId;
    })};
    if (entity == std::ranges::end(m_entities)) {
        return nullptr;
    }
    return *entity;
};

std::shared_ptr<Entity> EntityManager::getEntityByName(
    std::string_view entityName) const {
    auto entity{std::ranges::find_if(m_entities, [entityName](const auto& e) {
        return e->getEntityName() == entityName;
    })};
    if (entity == std::ranges::end(m_entities)) {
        return nullptr;
    }
    return *entity;
};

std::vector<std::shared_ptr<Entity>> EntityManager::getAllEntitiesWithTag(
    std::string_view tag) const {
    auto filtered = m_entities | std::views::filter([tag](const auto& e) {
                        return e->getEntityTag() == tag;
                    });
    return std::vector<std::shared_ptr<Entity>>(filtered.begin(),
                                                filtered.end());
}