#include "EntityManager.hpp"

#include <memory>

#include "Entity.hpp"

std::shared_ptr<Entity> EntityManager::createEntity() {
    std::shared_ptr<Entity> entity{new Entity{}};
    entity->m_entityName = "Teste";
    m_entities.push_back(entity);
    return entity;
}