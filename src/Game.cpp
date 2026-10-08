#include "Game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <string>

#include "Specifications.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

Game::~Game() { ImGui::SFML::Shutdown(); };

void Game::run() {
    parseConfigFile();
    std::println("Arquivo completo:\n{}", m_parsedConfigFile);
    createWindow();
    createFont();
    while (m_window.isOpen()) {
        processInput();
        update();
        render();
    }
};

void Game::createWindow() {
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

void Game::createFont() {
    auto fontData{std::ranges::find_if(m_parsedConfigFile,
                                       [](auto& e) { return e[0] == "Font"; })};
    if (fontData == m_parsedConfigFile.end()) {
        std::cerr << "Window not found on configuration file";
        return;
    }
    const FontSpec fSpec{*fontData};
    m_font = fSpec.toSfFont();
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

void Game::parseConfigFile() {
    std::ifstream file("config.txt");
    if (!file.is_open()) {
        return;
    }

    m_parsedConfigFile = tokenizeFile(file);
}

std::string Game::parseLine(std::ifstream& file) {
    std::string line{};
    std::getline(file, line);
    return line;
}

std::vector<std::string> Game::tokenize(std::string_view line,
                                        const char delimiter) {
    std::vector<std::string> tokenizedLine{};
    std::string token{};
    std::istringstream ss{line.data()};
    while (!ss.eof()) {
        std::getline(ss, token, delimiter);
        tokenizedLine.push_back(token);
    }
    return tokenizedLine;
}
std::vector<std::vector<std::string>> Game::tokenizeFile(
    std::ifstream& file, const char tokenDelimiter) {
    std::vector<std::vector<std::string>> tokenizedLines{};
    while (!file.eof()) {
        auto line{parseLine(file)};
        auto tokens{tokenize(line)};
        tokenizedLines.push_back(tokens);
    }
    return tokenizedLines;
}