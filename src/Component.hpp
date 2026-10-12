#ifndef COMPONENT_H
#define COMPONENT_H

#include <tuple>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"

class Component {
   public:
    bool m_exists{false};
};

class CShape : public Component {
   public:
    int m_shapeRadius{};
    int m_shapeVertices{};
    sf::Color m_fillColor{};
    sf::Color m_outlineColor{};
    int m_outlineThickness{};
    sf::CircleShape m_sfShape{};
};

class CCollision : public Component {
   public:
    int m_collisionRadius{};
};

class CTransform : public Component {
   public:
    int x{};
    int y{};
};

class CMovement : public Component {
   public:
    float m_minSpeed{};
    float m_maxSpeed{};
};

class CPlayerInput : public Component {
   public:
    bool m_top{};
    bool m_left{};
    bool m_down{};
    bool m_right{};
};

class CLifeSpan : public Component {
   public:
    int m_lifeSpan{};
};

class CSpawn : public Component {
   public:
    int m_spawnInterval{};
};

using ComponentContainer = std::tuple<CShape, CCollision, CTransform, CMovement,
                                      CPlayerInput, CLifeSpan, CSpawn>;

#endif  // COMPONENT_H