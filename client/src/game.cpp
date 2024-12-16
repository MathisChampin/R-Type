#include "../include/Game.hpp"
#include <iostream>

Game::Game()
    : m_window()
    , m_font()
    , m_currentState(GameState::Menu)
    , m_menu(m_window)
    , m_optionsMenu(m_window)
    , m_menuBackground(m_window.getSize(), {{"./assets/backgrounds/space_dust.png", 0.1f}})
    , m_playingBackground(m_window.getSize(), {{"./assets/backgrounds/space_dust.png", 0.2f}})
    , m_client()
    , m_ipAddress()
    , m_ipText()
    , m_ipField()
    , m_clock()
{
    initializeWindow();
    initializeFont();
    initializeMenuOptions();
    initializeIpAddressText();

    //FONCTION QUI FAIS GET DATA QUI REGARDE YA CB DE PLAYER DE CB ET D'ENNEMY PUIS JE PUSH BACK EN BALLE DANS LE VECTEUR

    // Initialize the player vector with one player
    // m_players.push_back(Player(sf::Vector2f(500, 500), m_client)); // Add the player
    // Initialize the enemies vector with a few enemies
    // m_enemies.push_back(Enemy(sf::Vector2f(1500, 500))); // Add the first enemy
    // m_enemies.push_back(Enemy(sf::Vector2f(1600, 600))); // Add another enemy
    // Add more enemies as needed
}

Game::~Game() {
    // Any cleanup if needed
}

void Game::initializeWindow() {
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    m_window.create(videoMode, "Menu SFML", sf::Style::Fullscreen);
    m_window.setFramerateLimit(60);
}

void Game::initializeFont() {
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf")) {
        std::cerr << "Impossible de charger la police!" << std::endl;
        throw std::runtime_error("Failed to load font");
    }
}

void Game::initializeMenuOptions() {
    // Initialize menu background layers
    std::vector<std::pair<std::string, float>> menuLayers = {
        {"./assets/backgrounds/space_dust.png", 0.1f},
    };
    std::vector<std::pair<std::string, float>> playingLayers = {
        {"./assets/backgrounds/space_dust.png", 0.2f},
    };

    m_menuBackground = ParallaxBackground(m_window.getSize(), menuLayers);
    m_playingBackground = ParallaxBackground(m_window.getSize(), playingLayers);

    // Add menu options with lambda functions
    m_menu.addOption("Jouer", [this]() {
        std::cout << "Démarrage du jeu..." << std::endl;
        m_currentState = GameState::Playing;
    });

    m_menu.addOption("Cree un lobby", [this]() {
        std::cout << "Création du lobby..." << std::endl;
        m_currentState = GameState::PlayingInLobby;
    });

    m_menu.addOption("Options", [this]() {
        std::cout << "Ouverture des options..." << std::endl;
        m_currentState = GameState::Options;
    });

    m_menu.addOption("Quitter", [this]() {
        std::cout << "Fermeture du jeu..." << std::endl;
        m_window.close();
    });
}

void Game::initializeIpAddressText() {
    m_ipAddress = "";

    m_ipText.setFont(m_font);
    m_ipText.setString("Entrez une IP:");
    m_ipText.setCharacterSize(25);
    m_ipText.setPosition(850, 270);

    m_ipField.setFont(m_font);
    m_ipField.setString(" ");
    m_ipField.setCharacterSize(25);
    m_ipField.setPosition(850, 310);
}

void Game::run() {
    while (m_window.isOpen()) {
        float deltaTime = m_clock.restart().asSeconds();
        
        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        processInput(event);
    }
}

void Game::processInput(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        m_window.close();
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            if (m_currentState != GameState::Menu) {
                m_currentState = GameState::Menu;
            } else {
                m_window.close();
            }
        }
    }

    // IP address input handling
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && m_ipAddress.getSize() > 0) {
            m_ipAddress.erase(m_ipAddress.getSize() - 1, 1);
        } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
            m_ipAddress += event.text.unicode;
        }
        m_ipField.setString(m_ipAddress);
    }

    // Delegate event handling to specific menus
    if (m_currentState == GameState::Menu) {
        m_menu.handleEvent(event);
    } else if (m_currentState == GameState::Options) {
        m_optionsMenu.handleEvent(event);
    }
}

void Game::update(float deltaTime) {
    // Update game components based on current state
    if (m_currentState == GameState::Menu) {
        m_menuBackground.update(deltaTime);
        m_menu.update();
    } else if (m_currentState == GameState::Playing) {
        // Update each player
        for (auto& player : m_players) {
            player.handleInput();
            player.update(deltaTime);
            player.sendQueuedMovements();
        }

        // Update each enemy
        for (auto& enemy : m_enemies) {
            enemy.update(deltaTime);
        }

        m_playingBackground.update(deltaTime);
    } else if (m_currentState == GameState::Options) {
        m_menuBackground.update(deltaTime);
        m_optionsMenu.update();
    }
}

void Game::render() {
    m_window.clear();

    // Render game components based on current state
    if (m_currentState == GameState::Menu) {
        m_menuBackground.render(m_window);
        m_menu.render();
        m_window.draw(m_ipText);
        m_window.draw(m_ipField);
    } else if (m_currentState == GameState::Playing) {
        m_playingBackground.render(m_window);

        // Render each player
        for (auto& player : m_players) {
            player.render(m_window);
        }

        // Render each enemy
        for (auto& enemy : m_enemies) {
            enemy.render(m_window);
        }
    } else if (m_currentState == GameState::Options) {
        m_menuBackground.render(m_window);
        m_optionsMenu.render();
    }

    m_window.display();
}
