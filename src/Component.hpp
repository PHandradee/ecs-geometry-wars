#ifndef COMPONENT_H
#define COMPONENT_H

#include <tuple>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"

class Component {};

class CShape : public Component {
   public:
    sf::CircleShape m_sfShape{};
    int m_shapeRadius{};
    int m_shapeVertices{};
    sf::Color m_fillColor{};
    sf::Color m_outlineColor{};
    sf::Color m_outLineTickness{};
};

class CCollision : public Component {
   public:
    int m_collisionRadius{};
};

using ComponentContainer = std::tuple<CShape, CCollision>;

#endif  // COMPONENT_H