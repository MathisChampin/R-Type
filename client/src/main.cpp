#include "../include/Menu.hpp"
#include "../include/ParallaxBackground.hpp"
#include "../include/Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState {
    Menu,
    Playing,
    Options,
    PlayingInLobby
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

void updateGame(float deltaTime, GameState currentState, ParallaxBackground& menuBackground, ParallaxBackground& playingBackground, Menu& menu) {
    if (currentState == GameState::Menu) {
        menuBackground.update(deltaTime);
        menu.update();
    } else if (currentState == GameState::Playing) {
        playingBackground.update(deltaTime);
    }
}

void renderGame(sf::RenderWindow& window, GameState currentState, ParallaxBackground& menuBackground, ParallaxBackground& playingBackground, Menu& menu, sf::Text& ipText, sf::Text& ipField, Player& player) {
    window.clear();

    if (currentState == GameState::Menu) {
        menuBackground.render(window);
        menu.render();
        window.draw(ipText);
        window.draw(ipField);
    } else if (currentState == GameState::Playing) {
        playingBackground.render(window);
        player.render(window);
    }

    window.display();
}

int main() {
    sf::RenderWindow window;
    initializeWindow(window);

    GameState currentState = GameState::Menu;

    std::vector<std::pair<std::string, float>> menuLayers = {
        {"./assets/backgrounds/space_dust.png", 0.1f},
        // {"./assets/backgrounds/space_dust.png", 0.3f} // si ont trouve un autre assets styler a ajouter
    };

    std::vector<std::pair<std::string, float>> playingLayers = {
        {"./assets/backgrounds/game_background1.png", 0.2f},
        // {"./assets/backgrounds/game_background2.png", 0.5f}, next lvl
    };

    ParallaxBackground menuBackground(window.getSize(), menuLayers);
    ParallaxBackground playingBackground(window.getSize(), playingLayers);

    sf::Clock clock;
    Menu menu(window);

    menu.addOption("Jouer", [&currentState]() {
        std::cout << "Démarrage du jeu..." << std::endl;
        currentState = GameState::Playing;
    });

    menu.addOption("Cree un lobby", [&currentState]() {
        std::cout << "Création du lobby..." << std::endl;
        currentState = GameState::PlayingInLobby;
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

    sf::Text ipField(" ", font, 25);
    ipField.setPosition(850, 310);

    Player player(sf::Vector2f(500, 500));

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;

        handleEvents(window, event, currentState, menu, ipAddress, ipField);

        if (currentState == GameState::Playing) {
            player.handleInput();
            player.update(deltaTime);
        }

        updateGame(deltaTime, currentState, menuBackground, playingBackground, menu);
        renderGame(window, currentState, menuBackground, playingBackground, menu, ipText, ipField, player);
    }

    return 0;
}
