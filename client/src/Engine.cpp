// Engine.cpp
#include "Engine.hpp"
#include <iostream>

Engine::Engine() : m_currentState(GameState::Menu)
{
    initializeWindow();
    initializeFont();
    initializeSoundManager();

    // Background layers
    std::vector<std::pair<std::string, float>> menuLayers = { {"assets/backgrounds/space_dust.png", 0.1f} };
    std::vector<std::pair<std::string, float>> playingLayers = { {"assets/backgrounds/space_dust.png", 0.2f} };

    m_menuBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), menuLayers);
    m_playingBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), playingLayers);
    m_customBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), playingLayers);

    // Menus
    m_menu = std::make_unique<Menu>(m_window);
    m_optionsMenu = std::make_unique<OptionsMenu>(m_window);
    m_customMenu = std::make_unique<CustomMenu>(m_window);

    // Menu options
    setupMenuOptions();
}

void Engine::initializeWindow()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    m_window.create(videoMode, "R-Type", sf::Style::Fullscreen);
    m_window.setFramerateLimit(60);
}

void Engine::initializeFont()
{
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf"))
    {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
        throw std::runtime_error("Échec du chargement de la police");
    }
}

void Engine::initializeSoundManager()
{
    if (!m_soundManager.loadMusic("background", "./assets/music/background.mp3"))
    {
        std::cerr << "Erreur : Impossible de charger la musique." << std::endl;
    }
    else if (!m_soundManager.playMusic("background", true))
    {
        std::cerr << "Erreur : La musique n'a pas pu être jouée." << std::endl;
    }
}

void Engine::setupMenuOptions()
{
    m_menu->addOption("Jouer", [this]()
    {
        std::cout << "Démarrage du jeu..." << std::endl;
        m_game = std::make_unique<Game>(m_creatorIp, m_window, m_customMenu.get()->getSelectedSkin(), m_font, *m_playingBackground, m_soundManager);
        m_currentState = GameState::Playing;
    });

    m_menu->addOption("Créer un lobby", [this]()
    {
        std::cout << "Création du lobby..." << std::endl;
        m_currentState = GameState::PlayingInLobby;
    });

    m_menu->addOption("Options", [this]()
    {
        std::cout << "Ouverture des options..." << std::endl;
        m_currentState = GameState::Options;
    });

    m_menu->addOption("Los Santos Custom", [this]()
    {
        std::cout << "Custom..." << std::endl;
        m_currentState = GameState::Custom;
    });

    m_menu->addOption("Quitter", [this]()
    {
        std::cout << "Fermeture du jeu..." << std::endl;
        m_window.close();
    });
}

void Engine::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            if (m_currentState == GameState::Custom || m_currentState == GameState::Options)
            {
                m_currentState = GameState::Menu;
            }
            else
            {
                m_window.close();
            }
        }

        switch (m_currentState)
        {
        case GameState::Menu:
            m_menu->handleEvent(event);
            break;
        case GameState::Options:
            m_optionsMenu->handleEvent(event);
            if (m_optionsMenu.get()->creatorIp.has_value()) {
                m_creatorIp = m_optionsMenu.get()->creatorIp.value();
                std::cout << "oh le boos" << m_creatorIp << std::endl;
            }
            break;
        case GameState::Custom:
            m_customMenu->handleEvent(event);
            break;
        case GameState::Playing:
            m_game.get()->handleEvents();
            break;
        case GameState::PlayingInLobby:
            break;
        case GameState::AnimationLevel:
            break;
        default:
            break;
        }
    }
}

void Engine::update(float deltaTime)
{
    switch (m_currentState)
    {
    case GameState::Menu:
        m_menuBackground->update(deltaTime);
        m_menu->update();
        break;
    case GameState::Options:
        m_menuBackground->update(deltaTime);
        m_optionsMenu->update();
        break;
    case GameState::Custom:
        m_customBackground->update(deltaTime);
        m_customMenu->update();
        break;
    case GameState::Playing:
        if (m_game.get()->AnimationLevel()) {
            std::cout << "Passage à AnimationLevel" << std::endl;
            m_game.get()->setPaused(true); // Met le jeu en pause
            m_currentState = GameState::AnimationLevel;
        } else {
            m_playingBackground->update(deltaTime);
            m_game.get()->update(deltaTime);
        }
        break;
    case GameState::AnimationLevel:
        break;
    default:
        break;
    }
}


void Engine::render(float deltaTime)
{
    m_window.clear();

    switch (m_currentState)
    {
    case GameState::Menu:
        m_menuBackground->render(m_window);
        m_menu->render();
        break;

    case GameState::Options:
        m_menuBackground->render(m_window);
        m_optionsMenu->render();
        break;

    case GameState::Custom:
        m_customBackground->render(m_window);
        m_customMenu->render();
        break;

    case GameState::Playing:
        m_playingBackground->render(m_window);
        m_game.get()->render(deltaTime);
        break;

    case GameState::PlayingInLobby:
        m_playingBackground->render(m_window);
        m_game.get()->render(deltaTime);
        break;

    case GameState::AnimationLevel:
    {
        std::cout << "je suis dans le render de animation level" << std::endl;
        // Bloc pour encapsuler l'utilisation de sf::Text
        m_window.clear(sf::Color::Black);

        sf::Text animationText;
        animationText.setFont(m_font);
        animationText.setString("Animation en cours...");
        animationText.setCharacterSize(50);
        animationText.setFillColor(sf::Color::White);
        animationText.setPosition(100, 100);

        m_window.draw(animationText);
        std::cout << "je sors du render d'animation" << std::endl;
        break; // Assurez-vous que le break reste dans ce bloc
    }

    default:
        break;
    }

    m_window.display();
}


void Engine::run()
{
    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();

        handleEvents();
        if (m_currentState == GameState::Playing) {
            std::cout << "je suis dans le engine run" << std::endl;
            m_game.get()->run();
        }
        update(deltaTime);
        render(deltaTime);
    }
}
