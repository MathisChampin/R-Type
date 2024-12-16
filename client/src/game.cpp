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
    , m_ipAddress()
    , m_ipText()
    , m_ipField()
    , m_clock()
{
    initializeWindow();
    initializeFont();
    initializeMenuOptions();
    initializeIpAddressText();
}

Game::~Game() {
    // Any cleanup if needed
}

void Game::get_player()
{
    auto packet = m_client.get_data();
    if (!packet.has_value())
        return;
    auto data = packet.value();
    if (data.getOpCode() != NmpClient::EVENT::SPRITE)
        return;
    auto spriteInfo = data.getSpriteInfo();
    bool playerExists = false;
    if (spriteInfo.id == 1) {
        for (auto& player : m_players) {
            if (player.get_id() == spriteInfo.idClient) {
                playerExists = true;
                player.updatePosition(sf::Vector2f(spriteInfo.x, spriteInfo.y));
                break;
            }
        }
        if (!playerExists) {
            if (spriteInfo.x >= 0 && spriteInfo.y >= 0) {
                m_players.push_back(Player(spriteInfo.idClient, sf::Vector2f(spriteInfo.x, spriteInfo.y), m_client));
                std::cout << "je suis en train de remplir player x = " << spriteInfo.x << " & y = " << spriteInfo.y << std::endl;
            } else {
                std::cerr << "Invalid player position received: x = " << spriteInfo.x << ", y = " << spriteInfo.y << std::endl;
            }
        }
    } else
        return; 
}

void Game::get_ennemies() {
    bool enemyExists = false;

    auto packet = m_client.get_data();
    if (!packet.has_value())
        return;
    auto data = packet.value();
    if (data.getOpCode() != NmpClient::EVENT::SPRITE)
        return;
    auto spriteInfo = data.getSpriteInfo();

    if (spriteInfo.id == 2) {
        for (auto& enemy : m_enemies) {
            if (enemy.get_id() == spriteInfo.idClient) {
                enemy.updatePosition(sf::Vector2f(spriteInfo.x, spriteInfo.y));
                enemyExists = true;
                break;
            }
        }
        if (!enemyExists) {
            if (spriteInfo.x >= 0 && spriteInfo.y >= 0) {
                m_enemies.push_back(Enemy(spriteInfo.idClient, sf::Vector2f(spriteInfo.x, spriteInfo.y)));
                std::cout << "je suis en train de remplir ennemi avec x = " << spriteInfo.x << " & y = " << spriteInfo.y << std::endl;
            } else {
                std::cerr << "Invalid enemy position received: x = " << spriteInfo.x << ", y = " << spriteInfo.y << std::endl;
            }
        }
    }
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
    std::vector<std::pair<std::string, float>> menuLayers = {
        {"./assets/backgrounds/space_dust.png", 0.1f},
    };
    std::vector<std::pair<std::string, float>> playingLayers = {
        {"./assets/backgrounds/space_dust.png", 0.2f},
    };
    m_menuBackground = ParallaxBackground(m_window.getSize(), menuLayers);
    m_playingBackground = ParallaxBackground(m_window.getSize(), playingLayers);

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
        std::cout << "JE SORS DE HANDLEEVENTS" << std::endl;
        get_ennemies();
        std::cout << "je sors de get ennemies" << std::endl;
        get_player();
        std::cout << "je sors de get player" << std::endl;
        update(deltaTime);
        render();
        std::cout << "JE SORS DE RENDER" << std::endl;
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
