#include "Entity.hpp"

int Entity::getEntityId() const { return m_entityId; };
std::string_view Entity::getEntityName() const { return m_entityName; }

void Entity::setEntityTag(std::string tag) { m_entityTag = tag; }

std::string_view Entity::getEntityTag() const { return m_entityTag; }
