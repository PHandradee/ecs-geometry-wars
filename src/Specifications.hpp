#ifndef SPECIFICATIONS_H
#define SPECIFICATIONS_H

#include <sys/types.h>

#include <cstdint>
#include <span>
#include <string>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowEnums.hpp"

class WindowSpec {
   public:
    WindowSpec(const std::span<std::string> tokenizedWLine)
        : m_width{std::stoi(tokenizedWLine[1])},
          m_height{std::stoi(tokenizedWLine[2])},
          m_frameLimit{std::stoi(tokenizedWLine[3])},
          m_fullScreen{std::stoi(tokenizedWLine[4])} {};

    const sf::VideoMode toVideoMode() const {
        const sf::VideoMode videoMode{
            {static_cast<uint>(m_width), static_cast<uint>(m_height)}};
        return videoMode;
    }

    int m_frameLimit{};
    sf::State m_fullScreen{};

   private:
    int m_width{};
    int m_height{};
};

class FontSpec {
   public:
    FontSpec(const std::span<std::string> tokenizedFLine)
        : fontFile{tokenizedFLine[1]},
          fontSize(std::stoi(tokenizedFLine[2])),
          color(std::stoi(tokenizedFLine[3]), std::stoi(tokenizedFLine[4]),
                std::stoi(tokenizedFLine[5])) {}

    const sf::Font toSfFont() const { return sf::Font{fontFile}; }

   private:
    int fontSize{};
    sf::Color color{};
    std::string fontFile{};
};

struct PlayerSpec {
    PlayerSpec(const std::span<std::string> tokenizedPLine)
        : m_shapeRadius{std::stoi(tokenizedPLine[1])},
          m_colRadius{std::stoi(tokenizedPLine[2])},
          m_speed{std::stof(tokenizedPLine[3])},
          m_fillColor{static_cast<uint8_t>(std::stoi(tokenizedPLine[4])),
                      static_cast<uint8_t>(std::stoi(tokenizedPLine[5])),
                      static_cast<uint8_t>(std::stoi(tokenizedPLine[6]))},
          m_outlineColor{static_cast<uint8_t>(std::stoi(tokenizedPLine[7])),
                         static_cast<uint8_t>(std::stoi(tokenizedPLine[8])),
                         static_cast<uint8_t>(std::stoi(tokenizedPLine[9]))},
          m_outlineThickness{std::stoi(tokenizedPLine[10])},
          m_shapeVertices{std::stoi(tokenizedPLine[11])} {}

    int m_shapeRadius{};
    int m_colRadius{};
    float m_speed{};
    sf::Color m_fillColor{};
    sf::Color m_outlineColor{};
    int m_outlineThickness{};
    int m_shapeVertices{};
};

class EnemySpec {
   public:
    EnemySpec(const std::span<std::string> tokenizedELine)
        : m_shapeRadius{std::stoi(tokenizedELine[1])},
          m_colRadius{std::stoi(tokenizedELine[2])},
          m_minSpeed{std::stof(tokenizedELine[3])},
          m_maxSpeed{std::stof(tokenizedELine[4])},
          m_outlineColor{static_cast<uint8_t>(std::stoi(tokenizedELine[5])),
                         static_cast<uint8_t>(std::stoi(tokenizedELine[6])),
                         static_cast<uint8_t>(std::stoi(tokenizedELine[7]))},
          m_outlineThickness{std::stoi(tokenizedELine[8])},
          m_minVertices{std::stoi(tokenizedELine[9])},
          m_maxVertices{std::stoi(tokenizedELine[10])},
          m_lifespan{std::stoi(tokenizedELine[11])},
          m_spawnInterval{std::stoi(tokenizedELine[12])} {}

   private:
    int m_shapeRadius{};
    int m_colRadius{};
    float m_minSpeed{};
    float m_maxSpeed{};
    sf::Color m_outlineColor{};
    int m_outlineThickness{};
    int m_minVertices{};
    int m_maxVertices{};
    int m_lifespan{};
    int m_spawnInterval{};
};

struct BulletSpec {
   public:
    BulletSpec(const std::span<std::string> tokenizedBLine)
        : m_shapeRadius{std::stoi(tokenizedBLine[1])},
          m_colRadius{std::stoi(tokenizedBLine[2])},
          m_speed{std::stof(tokenizedBLine[3])},
          m_fillColor{static_cast<uint8_t>(std::stoi(tokenizedBLine[4])),
                      static_cast<uint8_t>(std::stoi(tokenizedBLine[5])),
                      static_cast<uint8_t>(std::stoi(tokenizedBLine[6]))},
          m_outlineColor{static_cast<uint8_t>(std::stoi(tokenizedBLine[7])),
                         static_cast<uint8_t>(std::stoi(tokenizedBLine[8])),
                         static_cast<uint8_t>(std::stoi(tokenizedBLine[9]))},
          m_outlineThickness{std::stoi(tokenizedBLine[10])},
          m_shapeVertices{std::stoi(tokenizedBLine[11])},
          m_lifespan{std::stoi(tokenizedBLine[12])} {}

   private:
    int m_shapeRadius{};
    int m_colRadius{};
    float m_speed{};
    sf::Color m_fillColor{};
    sf::Color m_outlineColor{};
    int m_outlineThickness{};
    int m_shapeVertices{};
    int m_lifespan{};
};

#endif  // SPECIFICATIONS_H