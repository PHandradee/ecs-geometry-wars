#ifndef GAME_HPP
#define GAME_HPP

#include "EntityManager.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Game {
   public:
    Game();
    ~Game();

    void run();

   private:
    void processInput();
    void update();
    void render();

    sf::RenderWindow m_window{};
    EntityManager m_entityManager{EntityManager::getInstance()};
    sf::Clock m_deltaClock{};
};

#endif  // GAME_HPP