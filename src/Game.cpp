#include "Game.hpp"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <string>

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "SFML/System/Angle.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Specifications.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

Game::~Game() { ImGui::SFML::Shutdown(); };

auto Game::run() -> void {
    parseConfigFile();
    std::println("Arquivo completo:\n{}", m_parsedConfigFile);
    createWindow();
    createFont();
    createPlayer();
    while (m_window.isOpen()) {
        processInput();
        update();
        render();
    }
};

auto Game::createWindow() -> void {
    auto windowData{std::ranges::find_if(
        m_parsedConfigFile, [](auto& e) { return e[0] == "Window"; })};
    if (windowData == m_parsedConfigFile.end()) {
        std::cerr << "Window not found on configuration file";
        return;
    }

    const WindowSpec wSpec{*windowData};
    m_window =
        sf::RenderWindow{wSpec.toVideoMode(), "Test", wSpec.m_fullScreen};
    m_window.setFramerateLimit(wSpec.m_frameLimit);
    auto a{ImGui::SFML::Init(m_window)};
};

auto Game::createFont() -> void {
    auto fontData{std::ranges::find_if(m_parsedConfigFile,
                                       [](auto& e) { return e[0] == "Font"; })};
    if (fontData == m_parsedConfigFile.end()) {
        std::cerr << "Font not found on configuration file";
        return;
    }
    const FontSpec fSpec{*fontData};
    m_font = fSpec.toSfFont();
};

auto Game::createPlayer() -> void {
    auto playerData{std::ranges::find_if(
        m_parsedConfigFile, [](auto& e) { return e[0] == "Player"; })};
    if (playerData == m_parsedConfigFile.end()) {
        std::cerr << "Player not found on configuration file";
        return;
    }
    const PlayerSpec pSpec{*playerData};
    auto playerEntity{EntityManager::getInstance().createEntity("Player")};
    playerEntity->setEntityTag("Player");
    auto& playerShape{playerEntity->addComponent<CShape>()};
    playerShape.m_shapeRadius = pSpec.m_shapeRadius;
    playerShape.m_shapeVertices = pSpec.m_shapeVertices;
    playerShape.m_fillColor = pSpec.m_fillColor;
    playerShape.m_outlineColor = pSpec.m_outlineColor;
    playerShape.m_outlineThickness = pSpec.m_outlineThickness;
    playerShape.m_sfShape =
        sf::CircleShape{static_cast<float>(pSpec.m_shapeRadius),
                        static_cast<size_t>(pSpec.m_shapeVertices)};
    playerShape.m_sfShape.setOrigin({static_cast<float>(pSpec.m_shapeRadius),
                                     static_cast<float>(pSpec.m_shapeRadius)});
    playerShape.m_sfShape.setFillColor(pSpec.m_fillColor);
    playerShape.m_sfShape.setOutlineColor(pSpec.m_outlineColor);
    playerShape.m_sfShape.setOutlineThickness(
        static_cast<float>(pSpec.m_outlineThickness));
    playerShape.m_sfShape.setPosition(
        {m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f});

    auto& playerCollision{playerEntity->addComponent<CCollision>()};
    playerCollision.m_collisionRadius = pSpec.m_colRadius;
    auto& playerMovement{playerEntity->addComponent<CMovement>()};
    playerMovement.m_minSpeed = pSpec.m_speed;
    playerMovement.m_maxSpeed = pSpec.m_speed;
    playerEntity->addComponent<CTransform>();
    playerEntity->addComponent<CPlayerInput>();
};

auto Game::processInput() -> void {
    while (const auto event = m_window.pollEvent()) {
        ImGui::SFML::ProcessEvent(m_window, *event);

        if (auto& e{event.value()};
            e.is<sf::Event::KeyPressed>() && event.has_value()) {
            auto& keyPressedEvent{*e.getIf<sf::Event::KeyPressed>()};
            switch (keyPressedEvent.code) {
                case sf::Keyboard::Key::Escape: {
                    std::print("Escape key pressed, closing window\n");
                    m_window.close();

                    break;
                }
                case sf::Keyboard::Key::W:
                case sf::Keyboard::Key::Up: {
                    auto playerEntity{
                        EntityManager::getInstance().getAllEntitiesWithTag(
                            "Player")};
                    std::ranges::for_each(
                        playerEntity, [](std::shared_ptr<Entity> entity) {
                            if (entity->hasComponent<CPlayerInput>()) {
                                entity->getComponent<CPlayerInput>()->m_top =
                                    true;
                                std::print("PlayerInput m_top set to true\n");
                            }
                        });
                    break;
                }
                case sf::Keyboard::Key::A:
                case sf::Keyboard::Key::Left: {
                    auto playerEntity{
                        EntityManager::getInstance().getAllEntitiesWithTag(
                            "Player")};
                    std::ranges::for_each(
                        playerEntity, [](std::shared_ptr<Entity> entity) {
                            if (entity->hasComponent<CPlayerInput>()) {
                                entity->getComponent<CPlayerInput>()->m_left =
                                    true;
                                std::print("PlayerInput m_left set to true\n");
                            }
                        });
                    break;
                }
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down: {
                    auto playerEntity{
                        EntityManager::getInstance().getAllEntitiesWithTag(
                            "Player")};
                    std::ranges::for_each(
                        playerEntity, [](std::shared_ptr<Entity> entity) {
                            if (entity->hasComponent<CPlayerInput>()) {
                                entity->getComponent<CPlayerInput>()->m_down =
                                    true;
                                std::print("PlayerInput m_down set to true\n");
                            }
                        });
                    break;
                }
                case sf::Keyboard::Key::D:
                case sf::Keyboard::Key::Right: {
                    auto playerEntity{
                        EntityManager::getInstance().getAllEntitiesWithTag(
                            "Player")};
                    std::ranges::for_each(
                        playerEntity, [](std::shared_ptr<Entity> entity) {
                            if (entity->hasComponent<CPlayerInput>()) {
                                entity->getComponent<CPlayerInput>()->m_right =
                                    true;
                                std::print("PlayerInput m_right set to true\n");
                            }
                        });
                    break;
                }
                default:
                    break;
            }
        }

        if (auto& e{event.value()};
            e.is<sf::Event::KeyReleased>() && event.has_value()) {
            auto& keyReleasedEvent{*e.getIf<sf::Event::KeyReleased>()};
            switch (keyReleasedEvent.code) {
                case sf::Keyboard::Key::W:
                case sf::Keyboard::Key::Up: {
                    auto playerEntity{
                        EntityManager::getInstance().getAllEntitiesWithTag(
                            "Player")};
                    std::ranges::for_each(
                        playerEntity, [](std::shared_ptr<Entity> entity) {
                            if (entity->hasComponent<CPlayerInput>()) {
                                entity->getComponent<CPlayerInput>()->m_top =
                                    false;
                                std::print("PlayerInput m_top set to false\n");
                            }
                        });
                    break;
                }
                case sf::Keyboard::Key::A:
                case sf::Keyboard::Key::Left: {
                    auto playerEntity{
                        EntityManager::getInstance().getAllEntitiesWithTag(
                            "Player")};
                    std::ranges::for_each(
                        playerEntity, [](std::shared_ptr<Entity> entity) {
                            if (entity->hasComponent<CPlayerInput>()) {
                                entity->getComponent<CPlayerInput>()->m_left =
                                    false;
                                std::print("PlayerInput m_left set to false\n");
                            }
                        });
                    break;
                }
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down: {
                    auto playerEntity{
                        EntityManager::getInstance().getAllEntitiesWithTag(
                            "Player")};
                    std::ranges::for_each(
                        playerEntity, [](std::shared_ptr<Entity> entity) {
                            if (entity->hasComponent<CPlayerInput>()) {
                                entity->getComponent<CPlayerInput>()->m_down =
                                    false;
                                std::print("PlayerInput m_down set to false\n");
                            }
                        });
                    break;
                }
                case sf::Keyboard::Key::D:
                case sf::Keyboard::Key::Right: {
                    auto playerEntity{
                        EntityManager::getInstance().getAllEntitiesWithTag(
                            "Player")};
                    std::ranges::for_each(
                        playerEntity, [](std::shared_ptr<Entity> entity) {
                            if (entity->hasComponent<CPlayerInput>()) {
                                entity->getComponent<CPlayerInput>()->m_right =
                                    false;
                                std::print(
                                    "PlayerInput m_right set to false\n");
                            }
                        });
                    break;
                }
                default:
                    break;
            }
        }

        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
};
auto Game::update() -> void {
    const auto entities{EntityManager::getInstance().getAllEntities()};
    std::ranges::for_each(entities, [this](std::shared_ptr<Entity> entity) {
        if (entity->hasComponent<CShape>()) {
            auto& shape{entity->getComponent<CShape>()->m_sfShape};
            auto angle{sf::degrees(1.f)};
            shape.rotate(angle);
        }
    });

    ImGui::SFML::Update(m_window, m_deltaClock.restart());

    // ImGui::ShowDemom_window();

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();
};
auto Game::render() -> void {
    m_window.clear();
    // m_window.draw(shape);
    auto playerEntities{
        EntityManager::getInstance().getAllEntitiesWithTag("Player")};
    std::ranges::for_each(
        playerEntities, [this](std::shared_ptr<Entity> entity) {
            if (entity->hasComponent<CShape>()) {
                m_window.draw(entity->getComponent<CShape>()->m_sfShape);
            }
        });
    ImGui::SFML::Render(m_window);
    m_window.display();
};

auto Game::parseConfigFile() -> void {
    std::ifstream file("config.txt");
    if (!file.is_open()) {
        return;
    }

    m_parsedConfigFile = tokenizeFile(file);
}

auto Game::parseLine(std::ifstream& file) -> std::string {
    std::string line{};
    std::getline(file, line);
    return line;
}

auto Game::tokenize(std::string_view line, const char delimiter)
    -> std::vector<std::string> {
    std::vector<std::string> tokenizedLine{};
    std::string token{};
    std::istringstream ss{line.data()};
    while (!ss.eof()) {
        std::getline(ss, token, delimiter);
        tokenizedLine.push_back(token);
    }
    return tokenizedLine;
}
auto Game::tokenizeFile(std::ifstream& file, const char tokenDelimiter)
    -> std::vector<std::vector<std::string>> {
    std::vector<std::vector<std::string>> tokenizedLines{};
    while (!file.eof()) {
        auto line{parseLine(file)};
        auto tokens{tokenize(line)};
        tokenizedLines.push_back(tokens);
    }
    return tokenizedLines;
}