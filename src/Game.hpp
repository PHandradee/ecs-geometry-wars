#ifndef GAME_HPP
#define GAME_HPP

#include "EntityManager.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Game {
   public:
    Game() = default;
    ~Game();

    auto run() -> void;

   private:
    auto processInput() -> void;
    auto update() -> void;
    auto render() -> void;
    auto parseConfigFile() -> void;
    auto tokenize(std::string_view line, const char delimiter = ' ') -> std::vector<std::string>;
    auto tokenizeFile(std::ifstream& file, const char tokenDelimiter = ' ') -> std::vector<std::vector<std::string>>;
    auto parseLine(std::ifstream& file) -> std::string;

    auto createWindow() -> void;
    auto createFont() -> void;

    sf::RenderWindow m_window{};
    sf::Font m_font{};
    EntityManager m_entityManager{EntityManager::getInstance()};
    sf::Clock m_deltaClock{};
    std::vector<std::vector<std::string>> m_parsedConfigFile{};
};

#endif  // GAME_HPP