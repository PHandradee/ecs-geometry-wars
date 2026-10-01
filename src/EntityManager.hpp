#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <vector>

class Entity;

class EntityManager {
   public:
    std::shared_ptr<Entity> createEntity();
    std::shared_ptr<Entity> createEntity(std::string_view name);

    std::shared_ptr<Entity> getEntityById(const int entityId) const;
    std::shared_ptr<Entity> getEntityByName(std::string_view entityName) const;
    std::vector<std::shared_ptr<Entity>> getAllEntitiesWithTag(
        std::string_view tag) const;

    static EntityManager& getInstance() {
        static EntityManager instance{};
        return instance;
    }

   private:
    EntityManager() = default;
    std::vector<std::shared_ptr<Entity>> m_entities{};
    std::vector<std::shared_ptr<Entity>> m_markedToRemoveEntities{};
    int m_entitiesCount{0};
};

#endif  // ENTITY_MANAGER_HPP