#ifndef SPECIFICATIONS_H
#define SPECIFICATIONS_H

#include <future>
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

struct FontSpec {
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

#endif  // SPECIFICATIONS_H