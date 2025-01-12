#include "../include/Game.hpp"
#include <iostream>
#include <algorithm>

Game::Game()
    : m_window(),
      m_font(),
      m_currentState(GameState::Menu),
      m_menu(m_window),
      m_optionsMenu(m_window),
      m_menuBackground(m_window.getSize(), {{"./assets/backgrounds/space_dust.png", 0.1f}}),
      m_playingBackground(m_window.getSize(), {{"./assets/backgrounds/space_dust.png", 0.2f}}),
      m_players(m_client)
{
    initializeWindow();
    initializeFont();
    initializeMenuOptions();
    initializeIpAddressText();

    m_life.initialize("./assets/life/hearts.png");
}

Game::~Game()
{
    m_enemies.clear();
    m_shoots.clear();
}

void Game::initializeWindow()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    m_window.create(videoMode, "R-Type", sf::Style::Fullscreen);
    m_window.setFramerateLimit(60);
}

void Game::initializeFont()
{
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf"))
    {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
        throw std::runtime_error("Échec du chargement de la police");
    }
}

void Game::initializeMenuOptions()
{
    std::vector<std::pair<std::string, float>> menuLayers = {
        {"assets/backgrounds/space_dust.png", 0.1f},
    };
    std::vector<std::pair<std::string, float>> playingLayers = {
        {"assets/backgrounds/space_dust.png", 0.2f},
    };
    m_menuBackground = ParallaxBackground(m_window.getSize(), menuLayers);
    m_playingBackground = ParallaxBackground(m_window.getSize(), playingLayers);

    // Ajout des options du menu
    m_menu.addOption("Jouer", [this]() {
        std::cout << "Démarrage du jeu..." << std::endl;
        m_currentState = GameState::Playing;
    });

    m_menu.addOption("Créer un lobby", [this]() {
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

void Game::initializeIpAddressText()
{
    m_ipAddress = "";

    m_ipText.setFont(m_font);
    m_ipText.setString("Entrez une IP :");
    m_ipText.setCharacterSize(25);
    m_ipText.setPosition(850, 270);

    m_ipField.setFont(m_font);
    m_ipField.setString(" ");
    m_ipField.setCharacterSize(25);
    m_ipField.setPosition(850, 310);
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        processInput(event);
    }
}

void Game::processInput(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
    {
        m_window.close();
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            if (m_currentState != GameState::Menu)
            {
                m_currentState = GameState::Menu;
            }
            else
            {
                m_window.close();
            }
        }
    }

    // Gestion des événements en fonction de l'état
    if (m_currentState == GameState::Menu)
    {
        m_menu.handleEvent(event);
    }
    else if (m_currentState == GameState::Options)
    {
        m_optionsMenu.handleEvent(event);
    }
}

void Game::update(float deltaTime)
{
    if (m_currentState == GameState::Menu)
    {
        m_menuBackground.update(deltaTime);
        m_menu.update();
    }
    else if (m_currentState == GameState::Playing)
    {
        m_players.handleInput();
        m_players.sendQueuedMovements();
        m_playingBackground.update(deltaTime);
    }
    else if (m_currentState == GameState::Options)
    {
        m_menuBackground.update(deltaTime);
        m_optionsMenu.update();
    }
}

void Game::render(float deltaTime)
{
    m_window.clear();

    if (m_currentState == GameState::Menu)
    {
        m_menuBackground.render(m_window);
        m_menu.render();
        m_window.draw(m_ipText);
        m_window.draw(m_ipField);
    }
    else if (m_currentState == GameState::Playing)
    {
        m_playingBackground.render(m_window);
        _spriteMng.drawAll(m_window, sf::seconds(deltaTime));     
        m_life.render(m_window);
    }
    else if (m_currentState == GameState::Options)
    {
        m_menuBackground.render(m_window);
        m_optionsMenu.render();
    }

    m_window.display();
}
