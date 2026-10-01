#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <print>

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({640, 480}), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    auto& entityManager{EntityManager::getInstance()};

    auto entityA{entityManager.createEntity("Entidade A")};
    entityA->addComponent<CTransform>();
    if (entityA->hasComponent<CTransform>()) {
        auto transform{entityA->getComponent<CTransform>()};
        std::println("{} has transform of x:{},y{}", entityA->getEntityName(),
                     transform->x, transform->y);
    }
    auto entityB{entityManager.createEntity("Entidade B")};
    std::println("{} has id {}", entityA->getEntityName(),
                 entityA->getEntityId());
    std::println("{} has id {}", entityB->getEntityName(),
                 entityB->getEntityId());

    auto entityC{entityManager.getEntityById(999)};
    if (entityC == nullptr) {
        std::println("Entity with id 999 doesnt exits");
    }

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}