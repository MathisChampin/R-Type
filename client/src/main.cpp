#include "../include/Menu.hpp"
#include "../include/ParallaxBackground.hpp"
#include "../include/Player.hpp"
#include "../include/OptionsMenu.hpp"
#include "../include/client/Client.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
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

void handleEvents(sf::RenderWindow& window, sf::Event& event, GameState& currentState, Menu& menu, OptionsMenu& optionsMenu, sf::String& ipAddress, sf::Text& ipField) {
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
        } else if (currentState == GameState::Options) {
            optionsMenu.handleEvent(event);
        }
    }
}

void updateGame(float deltaTime, GameState currentState, ParallaxBackground& menuBackground, ParallaxBackground& playingBackground, Menu& menu, OptionsMenu& optionsMenu) {
    if (currentState == GameState::Menu) {
        menuBackground.update(deltaTime);
        menu.update();
    } else if (currentState == GameState::Playing) {
        playingBackground.update(deltaTime);
    } else if (currentState == GameState::Options) {
        menuBackground.update(deltaTime);
        optionsMenu.update();
    }
}

void renderGame(sf::RenderWindow& window, GameState currentState, ParallaxBackground& menuBackground, ParallaxBackground& playingBackground, Menu& menu, OptionsMenu& optionsMenu, sf::Text& ipText, sf::Text& ipField, Player& player) {
    window.clear();

    if (currentState == GameState::Menu) {
        menuBackground.render(window);
        menu.render();
        window.draw(ipText);
        window.draw(ipField);
    } else if (currentState == GameState::Playing) {
        playingBackground.render(window);
        player.render(window);
    } else if (currentState == GameState::Options) {
        menuBackground.render(window);
        optionsMenu.render();
    }

    window.display();
}

void listenToServer(NmpClient::Client& client) {
    while (true) {
        client.get_data();
    }
}

int main() {
    sf::RenderWindow window;
    initializeWindow(window);

    GameState currentState = GameState::Menu;

    NmpClient::Client client; // Crée une instance de Client pour la communication réseau
    Player player(sf::Vector2f(500, 500), client); // Passe Client en argument

    std::thread serverThread(listenToServer, std::ref(client)); // Thread d'écoute

    std::vector<std::pair<std::string, float>> menuLayers = {
        {"./assets/backgrounds/space_dust.png", 0.1f},
    };

    std::vector<std::pair<std::string, float>> playingLayers = {
        {"./assets/backgrounds/game_background1.png", 0.2f},
    };

    ParallaxBackground menuBackground(window.getSize(), menuLayers);
    ParallaxBackground playingBackground(window.getSize(), playingLayers);

    sf::Clock clock;
    Menu menu(window);
    OptionsMenu optionsMenu(window);

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

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;

        handleEvents(window, event, currentState, menu, optionsMenu, ipAddress, ipField);

        if (currentState == GameState::Playing) {
            player.handleInput();
            player.update(deltaTime);
        }

        updateGame(deltaTime, currentState, menuBackground, playingBackground, menu, optionsMenu);
        renderGame(window, currentState, menuBackground, playingBackground, menu, optionsMenu, ipText, ipField, player);
    }

    serverThread.join(); // Attendre que le thread se termine
    return 0;
}
