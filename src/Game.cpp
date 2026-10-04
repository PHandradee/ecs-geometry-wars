#include "Game.hpp"

#include "imgui-SFML.h"
#include "imgui.h"

Game::Game() : m_window(sf::VideoMode({640, 480}), "ImGui + SFML = <3") {
    m_window.setFramerateLimit(60);
    auto a{ImGui::SFML::Init(m_window)};
};
Game::~Game() { ImGui::SFML::Shutdown(); };

void Game::run() {
    while (m_window.isOpen()) {
        processInput();
        update();
        render();
    }
};

void Game::processInput() {
    while (const auto event = m_window.pollEvent()) {
        ImGui::SFML::ProcessEvent(m_window, *event);

        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
};
void Game::update() {
    ImGui::SFML::Update(m_window, m_deltaClock.restart());

    // ImGui::ShowDemom_window();

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();
};
void Game::render() {
    m_window.clear();
    // m_window.draw(shape);
    ImGui::SFML::Render(m_window);
    m_window.display();
};