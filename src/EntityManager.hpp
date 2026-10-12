#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <memory>
#include <vector>

class Entity;

class EntityManager {
   public:
    auto createEntity() -> std::shared_ptr<Entity>;
    auto createEntity(std::string_view name) -> std::shared_ptr<Entity>;

    auto getEntityById(const int entityId) const -> std::shared_ptr<Entity>;
    auto getEntityByName(std::string_view entityName) const
        -> std::shared_ptr<Entity>;
    auto getAllEntitiesWithTag(std::string_view tag) const
        -> std::vector<std::shared_ptr<Entity>>;

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