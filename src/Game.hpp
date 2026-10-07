#ifndef GAME_HPP
#define GAME_HPP

#include "EntityManager.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Game {
   public:
    Game() = default;
    ~Game();

    void run();

   private:
    void processInput();
    void update();
    void render();
    void parseConfigFile();
    std::vector<std::string> tokenize(std::string_view line,
                                      const char delimiter = ' ');
    std::vector<std::vector<std::string>> tokenizeFile(
        std::ifstream& file, const char tokenDelimiter = ' ');
    std::string parseLine(std::ifstream& file);

    void createWindow();

    sf::RenderWindow m_window{};
    EntityManager m_entityManager{EntityManager::getInstance()};
    sf::Clock m_deltaClock{};
    std::vector<std::vector<std::string>> m_parsedConfigFile{};
};

#endif  // GAME_HPP