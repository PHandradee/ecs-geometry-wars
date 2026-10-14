#include "EntityManager.hpp"

#include <algorithm>
#include <iterator>
#include <memory>
#include <ranges>

#include "Entity.hpp"

auto EntityManager::createEntity() -> std::shared_ptr<Entity> {
    ++m_entitiesCount;
    std::shared_ptr<Entity> entity{new Entity{m_entitiesCount}};
    m_entities.push_back(entity);
    return entity;
}

auto EntityManager::createEntity(std::string_view name)
    -> std::shared_ptr<Entity> {
    std::shared_ptr<Entity> entity{createEntity()};
    entity->setEntityName(name);
    return entity;
}

auto EntityManager::getEntityById(const int entityId) const
    -> std::shared_ptr<Entity> {
    auto entity{std::ranges::find_if(m_entities, [entityId](const auto& e) {
        return e->getEntityId() == entityId;
    })};
    if (entity == std::ranges::end(m_entities)) {
        return nullptr;
    }
    return *entity;
};

auto EntityManager::getEntityByName(std::string_view entityName) const
    -> std::shared_ptr<Entity> {
    auto entity{std::ranges::find_if(m_entities, [entityName](const auto& e) {
        return e->getEntityName() == entityName;
    })};
    if (entity == std::ranges::end(m_entities)) {
        return nullptr;
    }
    return *entity;
};

auto EntityManager::getAllEntitiesWithTag(std::string_view tag) const
    -> std::vector<std::shared_ptr<Entity>> {
    auto filtered = m_entities | std::views::filter([tag](const auto& e) {
                        return e->getEntityTag() == tag;
                    });
    return std::vector<std::shared_ptr<Entity>>(filtered.begin(),
                                                filtered.end());
}

auto EntityManager::getAllEntities() const
    -> std::vector<std::shared_ptr<Entity>> {
    return m_entities;
}
