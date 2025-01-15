// Engine.cpp
#include "Engine.hpp"
#include <iostream>

Engine::Engine() : m_currentState(GameState::Menu), m_animationTime(0.0f)
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
            m_currentState = GameState::AnimationLevel;
            m_animationTime = 0.0f; // Réinitialise le temps écoulé
        } else {
            m_playingBackground->update(deltaTime);
            m_game.get()->update(deltaTime);
        }
        break;
    case GameState::AnimationLevel:
        m_animationTime += deltaTime;
        if (m_animationTime >= 3.0f) {
            std::cout << "Fin de l'animation, retour au jeu" << std::endl;
            m_currentState = GameState::Playing;
        }
        break;
    default:
        break;
    }
}

void renderAnimationLevel(sf::RenderWindow& window, sf::Font& font, int level, const std::string& spriteFilePath, const std::string& message)
{
    window.clear(sf::Color::Black);

    sf::Vector2u windowSize = window.getSize();

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setString("Level " + std::to_string(level));
    levelText.setCharacterSize(50);
    levelText.setFillColor(sf::Color::White);
    
    sf::FloatRect levelBounds = levelText.getLocalBounds();
    levelText.setOrigin(levelBounds.width / 2, levelBounds.height / 2);
    levelText.setPosition(windowSize.x / 2, 50);

    sf::Texture texture;
    if (!texture.loadFromFile(spriteFilePath)) {
        std::cerr << "Erreur : Impossible de charger la texture depuis " << spriteFilePath << std::endl;
        return;
    }

    sf::Sprite sprite(texture);
    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    sprite.setPosition(windowSize.x / 4, windowSize.y / 2);
    sprite.setScale(2.0f, 2.0f);

    sf::Text messageText;
    messageText.setFont(font);
    messageText.setString(message);
    messageText.setCharacterSize(30);
    messageText.setFillColor(sf::Color::White);
    
    sf::FloatRect messageBounds = messageText.getLocalBounds();
    messageText.setOrigin(messageBounds.width / 2, messageBounds.height / 2);
    messageText.setPosition((windowSize.x / 4) * 3, windowSize.y / 2);
    window.draw(levelText);
    window.draw(sprite);
    window.draw(messageText);
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
        int currentLevel = m_game.get()->getLevel();
        std::string spritePath;
        std::string message;

        switch (currentLevel)
        {
        case 3:
            renderAnimationLevel(m_window, m_font, m_game.get()->getLevel(), "./assets/bullet/player/tir_player_2_1.png", "Key Z too unlock");
            break;
        case 4:
            renderAnimationLevel(m_window, m_font, m_game.get()->getLevel(), "./assets/bullet/player/tir_player_3_1.png", "Key E too unlock");
            break;
        case 5:
            renderAnimationLevel(m_window, m_font, m_game.get()->getLevel(), "./assets/bullet/player/tir_player_4_1.png", "Key R too unlock");
            break;
        case 6:
            renderAnimationLevel(m_window, m_font, m_game.get()->getLevel(), "./assets/bullet/player/tir_player_5_1.png", "Key T too unlock");
            break;
        default:
            break;
        }
        break;
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
