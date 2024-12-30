#include "../include/Game.hpp"
#include <iostream>
#include <algorithm>

Game::Game()
    : m_window()
    , m_font()
    , m_currentState(GameState::Menu)
    , m_menu(m_window)
    , m_optionsMenu(m_window)
    , m_menuBackground(m_window.getSize(), {{"assets/backgrounds/space_dust.png", 0.1f}})
    , m_playingBackground(m_window.getSize(), {{"assets/backgrounds/space_dust.png", 0.2f}})
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
    m_players.clear();
    m_enemies.clear();
    m_shoots.clear();
}

void Game::initializeWindow() {
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    m_window.create(videoMode, "R-Type", sf::Style::Fullscreen);
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
        {"assets/backgrounds/space_dust.png", 0.1f},
    };
    std::vector<std::pair<std::string, float>> playingLayers = {
        {"assets/backgrounds/space_dust.png", 0.2f},
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

void Game::get_player() {
    auto packet = m_client.get_data();
    if (!packet.has_value())
        return;
    auto data = packet.value();
    if (data.getOpCode() != NmpClient::EVENT::SPRITE)
        return;
    auto spriteInfo = data.getSpriteInfo();
    
    if (spriteInfo.id == 1) {
        auto it = std::find_if(m_players.begin(), m_players.end(),
            [&](const auto& player) { return player->get_id() == spriteInfo.idClient; });
            
        if (it == m_players.end()) {
            try {
                m_players.emplace_back(std::make_unique<Player>(
                    spriteInfo.idClient,
                    sf::Vector2f(spriteInfo.x, spriteInfo.y),
                    m_client,
                    "config/player.json"
                ));
            } catch (const std::exception& e) {
                std::cerr << "Error creating player: " << e.what() << std::endl;
            }
        } else {
            if (*it) {
                (*it)->updatePosition(sf::Vector2f(spriteInfo.x, spriteInfo.y));
            }
        }
    }
}

void Game::get_ennemies() {
    auto packet = m_client.get_data();
    if (!packet.has_value())
        return;
    auto data = packet.value();
    if (data.getOpCode() != NmpClient::EVENT::SPRITE)
        return;
    auto spriteInfo = data.getSpriteInfo();

    if (spriteInfo.id == 2) {
        auto it = std::find_if(m_enemies.begin(), m_enemies.end(),
            [&](const auto& enemy) { return enemy->get_id() == spriteInfo.idClient; });
            
        if (it == m_enemies.end()) {
            try {
                m_enemies.emplace_back(std::make_unique<Enemy>(
                    spriteInfo.idClient,
                    sf::Vector2f(spriteInfo.x, spriteInfo.y),
                    "config/enemy.json"
                ));
            } catch (const std::exception& e) {
                std::cerr << "Error creating enemy: " << e.what() << std::endl;
            }
        } else {
            if (*it) {
                (*it)->updatePosition(sf::Vector2f(spriteInfo.x, spriteInfo.y));
            }
        }
    }
}

void Game::get_shoots() {
    auto packet = m_client.get_data();
    if (!packet.has_value())
        return;
    auto data = packet.value();
    if (data.getOpCode() != NmpClient::EVENT::SPRITE)
        return;
    auto spriteInfo = data.getSpriteInfo();

    if (spriteInfo.id == 3) {
        auto it = std::find_if(m_shoots.begin(), m_shoots.end(),
            [&](const auto& shoot) { return shoot->get_id() == spriteInfo.idClient; });
            
        if (it == m_shoots.end()) {
            try {
                m_shoots.emplace_back(std::make_unique<Shoot>(
                    spriteInfo.idClient,
                    sf::Vector2f(spriteInfo.x, spriteInfo.y)
                ));
            } catch (const std::exception& e) {
                std::cerr << "Error creating shoot: " << e.what() << std::endl;
            }
        } else {
            if (*it) {
                (*it)->updatePosition(sf::Vector2f(spriteInfo.x, spriteInfo.y));
            }
        }
    }
}

void Game::run() {
    while (m_window.isOpen()) {
        try {
            float deltaTime = m_clock.restart().asSeconds();
            handleEvents();
            get_ennemies();
            get_player();
            get_shoots();
            update(deltaTime);
            render();
        } catch (const std::exception& e) {
            std::cerr << "Error in game loop: " << e.what() << std::endl;
        }
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

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && m_ipAddress.getSize() > 0) {
            m_ipAddress.erase(m_ipAddress.getSize() - 1, 1);
        } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
            m_ipAddress += event.text.unicode;
        }
        m_ipField.setString(m_ipAddress);
    }

    if (m_currentState == GameState::Menu) {
        m_menu.handleEvent(event);
    } else if (m_currentState == GameState::Options) {
        m_optionsMenu.handleEvent(event);
    }
}

void Game::update(float deltaTime) {
    if (m_currentState == GameState::Menu) {
        m_menuBackground.update(deltaTime);
        m_menu.update();
    } else if (m_currentState == GameState::Playing) {
        for (auto& player : m_players) {
            if (player) {
                player->handleInput();
                player->update(deltaTime);
                player->sendQueuedMovements();
            }
        }

        for (auto& enemy : m_enemies) {
            if (enemy) {
                enemy->updatePosition(enemy->getPosition());  // Remplacé update par updatePosition
            }
        }

        for (auto& shoot : m_shoots) {
            if (shoot) {
                shoot->updatePosition(shoot->getPosition());  // Remplacé update par updatePosition
            }
        }

        m_playingBackground.update(deltaTime);
    } else if (m_currentState == GameState::Options) {
        m_menuBackground.update(deltaTime);
        m_optionsMenu.update();
    }
}

void Game::render() {
    m_window.clear();

    if (m_currentState == GameState::Menu) {
        m_menuBackground.render(m_window);
        m_menu.render();
        m_window.draw(m_ipText);
        m_window.draw(m_ipField);
    } else if (m_currentState == GameState::Playing) {
        m_playingBackground.render(m_window);
        
        for (const auto& player : m_players) {
            if (player) {
                player->render(m_window);
            }
        }

        for (const auto& enemy : m_enemies) {
            if (enemy) {
                enemy->render(m_window);
            }
        }

        for (const auto& shoot : m_shoots) {
            if (shoot) {
                shoot->render(m_window);
            }
        }
    } else if (m_currentState == GameState::Options) {
        m_menuBackground.render(m_window);
        m_optionsMenu.render();
    }

    m_window.display();
}