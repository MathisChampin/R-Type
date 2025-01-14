// Game.cpp
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
      m_customBackground(m_window.getSize(), {{"./assets/backgrounds/space_dust.png", 0.2f}}),
      m_client(std::nullopt),
      m_players(std::nullopt),
      m_CustomMenu(m_window),
      m_SoundManager()
{
    initializeWindow();
    initializeFont();
    initializeMenuOptions();
    initializeIpAddressText();

    if (!m_SoundManager.loadMusic("background", "./assets/music/background.mp3"))
    {
        std::cerr << "Erreur : Impossible de charger la musique." << std::endl;
    }
    else
    {
        if (!m_SoundManager.playMusic("background", true))
        {
            std::cerr << "Erreur : La musique n'a pas pu être jouée." << std::endl;
        }
        else
        {
            std::cout << "Musique en lecture." << std::endl;
        }
    }

    m_life.initialize("./assets/life/hearts.png", 5, 15.f);
    m_score.initialize(m_font, 30, sf::Vector2f(20, 60));
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
    m_customBackground = ParallaxBackground(m_window.getSize(), playingLayers);

    m_menu.addOption("Jouer", [this]()
                     {
                         std::cout << "Démarrage du jeu..." << std::endl;
                         initializeGameComponents();
                         m_currentState = GameState::Playing; });

    m_menu.addOption("Créer un lobby", [this]()
                     {
                         std::cout << "Création du lobby..." << std::endl;
                         initializeGameComponents();
                         m_currentState = GameState::PlayingInLobby; });

    m_menu.addOption("Options", [this]()
                     {
                         std::cout << "Ouverture des options..." << std::endl;
                         m_currentState = GameState::Options; });

    m_menu.addOption("Los Santos Custom", [this]()
                     {
                            std::cout << "Custom..." << std::endl;
                            m_currentState = GameState::Custom; });

    m_menu.addOption("Quitter", [this]()
                     {
                         std::cout << "Fermeture du jeu..." << std::endl;
                         m_window.close(); });
    
}

void Game::initializeGameComponents()
{
    m_client.emplace();  // Initialize client
    m_players.emplace(*m_client);  // Initialize player with reference to client
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
            if (m_currentState == GameState::Playing || m_currentState == GameState::PlayingInLobby)
            {
                // Reset game components when returning to menu
                m_client = std::nullopt;
                m_players = std::nullopt;
            }
            
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

    if (m_currentState == GameState::Menu)
    {
        m_menu.handleEvent(event);
    }
    else if (m_currentState == GameState::Options)
    {
        m_optionsMenu.handleEvent(event);
    }
    else if (m_currentState == GameState::Custom)
    {
        m_CustomMenu.handleEvent(event);
    }
}

void Game::update(float deltaTime)
{
    if (m_currentState == GameState::Menu)
    {
        m_menuBackground.update(deltaTime);
        m_menu.update();
    }
    else if (m_currentState == GameState::Playing || m_currentState == GameState::PlayingInLobby)
    {
        if (m_players.has_value())
        {
            m_players->handleInput();
            m_players->sendQueuedMovements();
        }
        m_playingBackground.update(deltaTime);
    }
    else if (m_currentState == GameState::Options)
    {
        m_menuBackground.update(deltaTime);
        m_optionsMenu.update();
    }
    else if (m_currentState == GameState::Custom)
    {
        m_customBackground.update(deltaTime);
        m_CustomMenu.update();
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
    else if (m_currentState == GameState::Playing || m_currentState == GameState::PlayingInLobby)
    {
        m_playingBackground.render(m_window);
        _spriteMng.drawAll(m_window, sf::seconds(deltaTime));
        m_life.render(m_window);
        m_score.render(m_window);
    }
    else if (m_currentState == GameState::Options)
    {
        m_menuBackground.render(m_window);
        m_optionsMenu.render();
    }
    else if (m_currentState == GameState::Custom)
    {
        m_customBackground.render(m_window);
        m_CustomMenu.render();
    }
    m_window.display();
}
