#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <string_view>
#include <tuple>

class Component;

// using ComponentContainer = std::tuple<Component>;

class Entity {
   public:
    int getEntityId() const;
    std::string_view getEntityName() const;

    void setEntityTag(std::string tag);
    std::string_view getEntityTag() const;

    template <typename T>
    T& addComponent();
    template <typename T>
    void removeComponent();
    template <typename T>
    T& getComponent() const;

   private:
    int m_entityId{};
    std::string m_entityName{};
    std::string m_entityTag{};
    // ComponentContainer m_components{};

    Entity() = default;
    ~Entity() = default;
};

#endif  // ENTITY_HPP
