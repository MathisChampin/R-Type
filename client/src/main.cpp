#include "../include/Menu.hpp"
#include "../include/ParallaxBackground.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState {
    Menu,
    Playing,
    Options
};

void initializeWindow(sf::RenderWindow& window) {
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    window.create(videoMode, "Menu SFML", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
}

void initializeFont(sf::Font& font) {
    if (!font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf")) {
        std::cerr << "Impossible de charger la police!" << std::endl;
        exit(-1);
    }
}

void handleEvents(sf::RenderWindow& window, sf::Event& event, GameState& currentState, Menu& menu, sf::String& ipAddress, sf::Text& ipField) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (currentState != GameState::Menu) {
                    currentState = GameState::Menu;
                } else {
                    window.close();
                }
            }
        }

        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b' && ipAddress.getSize() > 0) {
                ipAddress.erase(ipAddress.getSize() - 1, 1);
            } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                ipAddress += event.text.unicode;
            }
            ipField.setString(ipAddress);
        }

        if (currentState == GameState::Menu) {
            menu.handleEvent(event);
        }
    }
}

void updateGame(float deltaTime, GameState currentState, ParallaxBackground& background, Menu& menu) {
    background.update(deltaTime);

    if (currentState == GameState::Menu) {
        menu.update();
    }
}

void renderGame(sf::RenderWindow& window, GameState currentState, ParallaxBackground& background, Menu& menu, sf::Text& ipText, sf::Text& ipField) {
    window.clear();

    background.render(window);

    switch (currentState) {
        case GameState::Menu:
            menu.render();
            window.draw(ipText);
            window.draw(ipField);
            break;
        case GameState::Playing:
            break;
        case GameState::Options:
            break;
    }

    window.display();
}

int main() {
    sf::RenderWindow window;
    initializeWindow(window);

    GameState currentState = GameState::Menu;
    ParallaxBackground background(window.getSize());
    sf::Clock clock;
    Menu menu(window);

    menu.addOption("Jouer", [&currentState]() {
        std::cout << "Démarrage du jeu..." << std::endl;
        currentState = GameState::Playing;
    });

    menu.addOption("Options", [&currentState]() {
        std::cout << "Ouverture des options..." << std::endl;
        currentState = GameState::Options;
    });

    menu.addOption("Quitter", [&window]() {
        std::cout << "Fermeture du jeu..." << std::endl;
        window.close();
    });

    sf::String ipAddress = "";
    sf::Font font;
    initializeFont(font);

    sf::Text ipText("Entrez une IP:", font, 25);
    ipText.setPosition(850, 270);

    sf::Text ipField("", font, 25);
    ipField.setPosition(850, 310);

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        handleEvents(window, event, currentState, menu, ipAddress, ipField);
        updateGame(deltaTime, currentState, background, menu);
        renderGame(window, currentState, background, menu, ipText, ipField);
    }

    return 0;
}
