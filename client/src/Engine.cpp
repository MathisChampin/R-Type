#include "Engine.hpp"
#include <iostream>

Engine::Engine() : m_currentState(GameState::Menu), m_animationTime(0.0f)
{
    initializeWindow();
    initializeFont();
    initializeSoundManager();

    // Background layers
    std::vector<std::pair<std::string, float>> menuLayers = {
        {"assets/backgrounds/parallax-space-backgound.png", 0.1f},
        {"assets/backgrounds/parallax-space-stars.png", 0.2f}
    };
    std::vector<std::pair<std::string, float>> playingLayers = {
        {"assets/backgrounds/parallax-space-backgound.png", 0.1f},
        {"assets/backgrounds/parallax-space-stars.png", 0.2f},
        {"assets/backgrounds/parallax-space-far-planets.png", 0.3f}
    };
    std::vector<std::pair<std::string, float>> levelLayers = {
        {"assets/backgrounds/back2.jpg", 0.3f},
        {"assets/backgrounds/back1.png", -0.1f},
    };

    m_menuBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), menuLayers);
    m_playingBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), playingLayers);
    m_levelBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), levelLayers);

    m_customBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), playingLayers);
    m_infosBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), menuLayers);

    // Menus
    m_menu = std::make_unique<Menu>(m_window);
    m_optionsMenu = std::make_unique<OptionsMenu>(m_window);
    m_customMenu = std::make_unique<CustomMenu>(m_window);

    // Infos
    m_infoSection = std::make_unique<Infos>(m_window, m_font);

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
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
        throw std::runtime_error("Échec du chargement de la police");
    }
}

void Engine::initializeSoundManager()
{
    if (!m_soundManager.loadMusic("background", "./assets/music/background.mp3")) {
        std::cerr << "Erreur : Impossible de charger la musique." << std::endl;
    } else if (!m_soundManager.playMusic("background", true)) {
        std::cerr << "Erreur : La musique n'a pas pu être jouée." << std::endl;
    }
}

// Function to trigger the popup
void Engine::triggerPopup(const std::string& spritePath, const std::string& message)
{
    if (m_popupTexture.loadFromFile(spritePath)) {
        m_popupSprite.setTexture(m_popupTexture);
        m_popupMessage = message;
        m_showPopup = true;
        m_animationTime = 0.0f;
    } else {
        std::cerr << "Erreur : Impossible de charger la texture depuis " << spritePath << std::endl;
    }
}

void Engine::setupMenuOptions()
{
    m_menu->addOption("Play", [this]() {
        std::cout << "Démarrage du jeu..." << std::endl;
        m_game = std::make_unique<Game>(m_creatorIp, m_window, m_customMenu.get()->getSelectedSkin(), m_font, *m_playingBackground, m_soundManager);
        m_currentState = GameState::Playing;
    });

    // m_menu->addOption("Créer un lobby", [this]() {
    //     std::cout << "Création du lobby..." << std::endl;
    //     m_currentState = GameState::PlayingInLobby;
    // });

    m_menu->addOption("Multiplayer", [this]() {
        std::cout << "Ouverture des options..." << std::endl;
        m_currentState = GameState::Options;
    });

    m_menu->addOption("Infos", [this]() {
        std::cout << "Infos..." << std::endl;
        m_currentState = GameState::Infos;
    
        // Player Section
        m_infoSection->addText("Player", sf::Color::White, 30, true);
        auto playerTexture = std::make_shared<sf::Texture>();
        if (playerTexture->loadFromFile("./assets/player/sprite_1.png")) {
            m_infoSection->addItem(playerTexture, "Player", false, 2.0f, 2.0f);
        }
    
        // Enemies Section
        m_infoSection->addText("Enemies", sf::Color::White, 30, true);
        auto enemyTexture1 = std::make_shared<sf::Texture>();
        if (enemyTexture1->loadFromFile("./assets/enemy/sprite_1.png")) {
            m_infoSection->addItem(enemyTexture1, "Enemy 1", false, 2.0f, 2.0f);
        }
        auto enemyTexture2 = std::make_shared<sf::Texture>();
        if (enemyTexture2->loadFromFile("./assets/enemy/Dove_part_1_rotated.png")) {
            m_infoSection->addItem(enemyTexture2, "Enemy 2 - Dove", false, 2.0f, 2.0f);
        }
        auto enemyTexture3 = std::make_shared<sf::Texture>();
        if (enemyTexture3->loadFromFile("./assets/enemy/Ligher_part_1_rotated.png")) {
            m_infoSection->addItem(enemyTexture3, "Enemy 3 - Ligher", false, 2.0f, 2.0f);
        }
        auto enemyTexture4 = std::make_shared<sf::Texture>();
        if (enemyTexture4->loadFromFile("./assets/enemy/Lightning_part_1_rotated.png")) {
            m_infoSection->addItem(enemyTexture4, "Enemy 4 - Lightning", false, 2.0f, 2.0f);
        }
    
        // Boss Section
        m_infoSection->addText("Boss", sf::Color::White, 30, true);
        auto bossTexture = std::make_shared<sf::Texture>();
        if (bossTexture->loadFromFile("./assets/boss/boss_1_1.png")) {
            m_infoSection->addItem(bossTexture, "Boss", false, 0.5f, 0.5f);
        }
    
        // Powerups Section
        m_infoSection->addText("Powerups", sf::Color::White, 30, true);
        auto powerupTexture1 = std::make_shared<sf::Texture>();
        if (powerupTexture1->loadFromFile("./assets/powerup/life/powerup_life_1.png")) {
            m_infoSection->addItem(powerupTexture1, "Power Up Life", false, 0.7f, 0.7f);
        }
        auto powerupTexture2 = std::make_shared<sf::Texture>();
        if (powerupTexture2->loadFromFile("./assets/powerup/move/powerup_move_1.png")) {
            m_infoSection->addItem(powerupTexture2, "Power Up Move", false, 0.9f, 0.9f);
        }
    
        // Shoots Section
        auto shootsTitle = std::make_shared<sf::Text>();
        shootsTitle->setString("Shoots");
        shootsTitle->setFont(m_font);
        shootsTitle->setCharacterSize(30);
        shootsTitle->setFillColor(sf::Color::White);
        shootsTitle->setStyle(sf::Text::Bold);

        sf::Vector2u windowSize = m_window.getSize();
        float titleX = windowSize.x - shootsTitle->getGlobalBounds().width - 50.0f;
        float titleY = 50.0f;
        shootsTitle->setPosition(titleX, titleY);

        m_infoSection->addCustomText(shootsTitle);

        float shootYOffset = -700.0f;

        auto shootTexture1 = std::make_shared<sf::Texture>();
        if (shootTexture1->loadFromFile("./assets/lettre_a.png")) {
            m_infoSection->addItem(shootTexture1, "Shoot of level 1", true, 0.1f, 0.1f, shootYOffset);
        }
        auto shootTexture2 = std::make_shared<sf::Texture>();
        if (shootTexture2->loadFromFile("./assets/lettre_z.png")) {
            m_infoSection->addItem(shootTexture2, "Shoot of level 3", true, 0.1f, 0.1f, shootYOffset);
        }
        auto shootTexture3 = std::make_shared<sf::Texture>();
        if (shootTexture3->loadFromFile("./assets/lettre_e.png")) {
            m_infoSection->addItem(shootTexture3, "Shoot of level 4", true, 0.1f, 0.1f, shootYOffset);
        }
        auto shootTexture4 = std::make_shared<sf::Texture>();
        if (shootTexture4->loadFromFile("./assets/lettre_r.png")) {
            m_infoSection->addItem(shootTexture4, "Shoot of level 5", true, 0.1f, 0.1f, shootYOffset);
        }
        auto shootTexture5 = std::make_shared<sf::Texture>();
        if (shootTexture5->loadFromFile("./assets/lettre_t.png")) {
            m_infoSection->addItem(shootTexture5, "Shoot of level 6", true, 0.1f, 0.1f, shootYOffset);
        }
    });

    m_menu->addOption("Los Santos Custom", [this]() {
        std::cout << "Custom..." << std::endl;
        m_currentState = GameState::Custom;
    });

    m_menu->addOption("Leave", [this]() {
        std::cout << "Fermeture du jeu..." << std::endl;
        m_window.close();
    });
}

void Engine::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            if (m_currentState == GameState::Custom || m_currentState == GameState::Options || m_currentState == GameState::Infos) {
                m_currentState = GameState::Menu;
            } else {
                m_window.close();
            }
        }

        switch (m_currentState) {
        case GameState::Menu:
            m_menu->handleEvent(event);
            break;
        case GameState::Options:
            m_optionsMenu->handleEvent(event);
            if (m_optionsMenu.get()->creatorIp.has_value()) {
                m_creatorIp = m_optionsMenu.get()->creatorIp.value();
                // std::cout << "oh le boos" << m_creatorIp << std::endl;
            }
            break;
        case GameState::Infos:
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
        case GameState::AnimationLevelGame:
            break;
        default:
            break;
        }
    }
}

void Engine::update(float deltaTime)
{
    switch (m_currentState) {
    case GameState::Menu:
        m_menuBackground->update(deltaTime);
        m_menu->update();
        break;
    case GameState::Options:
        m_menuBackground->update(deltaTime);
        m_optionsMenu->update();
        break;
    case GameState::Infos:
        m_infosBackground->update(deltaTime);
        break;
    case GameState::Custom:
        m_customBackground->update(deltaTime);
        m_customMenu->update();
        break;
    case GameState::Playing:
        if (m_showPopup) {
            m_animationTime += deltaTime;
            if (m_animationTime >= 2.0f) {
                m_showPopup = false;
            }
        }
        if (m_game.get()->AnimationLevelGame()) {
            std::cout << "je suis dans le update du jeu pour changer de level" << std::endl;
            m_currentState = GameState::AnimationLevelGame;
            m_animationTime = 0.0f;
        } else {
            m_playingBackground->update(deltaTime);
            m_game.get()->update(deltaTime);
            if (m_game.get()->AnimationLevel()) {
                int currentLevel = m_game->getLevel();
                std::string spritePath;
                std::string message;

                switch (currentLevel) {
                case 3:
                    spritePath = "./assets/bullet/player/resized_tir_player_2_1.png";
                    message = "Key Z unlocked!";
                    break;
                case 4:
                    spritePath = "./assets/bullet/player/resized_tir_player_3_1.png";
                    message = "Key E unlocked!";
                    break;
                case 5:
                    spritePath = "./assets/bullet/player/resized_tir_player_4_1.png";
                    message = "Key R unlocked!";
                    break;
                case 6:
                    spritePath = "./assets/bullet/player/resized_tir_player_5_1.png";
                    message = "Key T unlocked!";
                    break;
                default:
                    break;
                }
                if (!spritePath.empty()) {
                    triggerPopup(spritePath, message);
                }
            }
            break;
        }
        break;
    case GameState::AnimationLevel:
        std::cout << "update animation player" << std::endl;
        m_animationTime += deltaTime;
        if (m_animationTime >= 2.0f) {
            m_currentState = GameState::Playing;
        }
        break;
    case GameState::AnimationLevelGame:
        std::cout << "update animation game" << std::endl;
        m_levelBackground->update(deltaTime);
        m_animationTime += deltaTime;
        if (m_animationTime >= 3.0f) {
            m_currentState = GameState::Playing;
        }
        break;
    default:
        break;
    }
}

void renderAnimationNewFile(sf::RenderWindow& window, sf::Font& font, int level) {
    sf::Vector2u windowSize = window.getSize();

    sf::Text topMessageText;
    topMessageText.setFont(font);
    topMessageText.setString("New wave of enemies loading...");
    topMessageText.setCharacterSize(30);
    topMessageText.setFillColor(sf::Color::White);

    sf::FloatRect topMessageBounds = topMessageText.getLocalBounds();
    topMessageText.setOrigin(topMessageBounds.width / 2, topMessageBounds.height / 2);
    topMessageText.setPosition(windowSize.x / 2, 50);

    sf::Text centerText;
    centerText.setFont(font);
    centerText.setString("Wave: " + std::to_string(level));
    centerText.setCharacterSize(50);
    centerText.setFillColor(sf::Color::White);

    sf::FloatRect centerTextBounds = centerText.getLocalBounds();
    centerText.setOrigin(centerTextBounds.width / 2, centerTextBounds.height / 2);
    centerText.setPosition(windowSize.x / 2, windowSize.y / 2);

    window.draw(topMessageText);
    window.draw(centerText);
}

void Engine::renderPopup()
{
    if (!m_showPopup) return;

    // Créez le texte pour mesurer sa largeur
    sf::Text popupText;
    popupText.setFont(m_font);
    popupText.setString(m_popupMessage);
    popupText.setCharacterSize(20); // Taille du texte
    popupText.setFillColor(sf::Color::White); // Couleur blanche

    sf::FloatRect textBounds = popupText.getLocalBounds();

    // Mise à l'échelle de la sprite
    float spriteScale = 1.5f;
    m_popupSprite.setScale(spriteScale, spriteScale);
    sf::FloatRect spriteBounds = m_popupSprite.getGlobalBounds();

    // Calcul de la largeur nécessaire pour la box
    float padding = 20.0f; // Espacement entre éléments et marges
    float boxWidth = padding + spriteBounds.width + padding + textBounds.width + padding;
    float boxHeight = std::max(spriteBounds.height, textBounds.height) + 2 * padding;

    // Création de la box noire pour la popup
    sf::RectangleShape popupBackground(sf::Vector2f(boxWidth, boxHeight));
    popupBackground.setFillColor(sf::Color(0, 0, 0, 200)); // Couleur noire semi-transparente
    popupBackground.setOutlineColor(sf::Color::White);     // Bordure blanche
    popupBackground.setOutlineThickness(2.0f);            // Épaisseur de la bordure
    popupBackground.setPosition((m_window.getSize().x - popupBackground.getSize().x) / 2, 50); // Centrer horizontalement

    // Position de la sprite
    float spriteOffsetX = popupBackground.getPosition().x + padding;
    float spriteOffsetY = popupBackground.getPosition().y + (popupBackground.getSize().y - spriteBounds.height) / 2.0f;
    m_popupSprite.setPosition(spriteOffsetX, spriteOffsetY);

    // Position du texte
    float textOffsetX = spriteOffsetX + spriteBounds.width + padding; // Décalage après la sprite
    float textOffsetY = popupBackground.getPosition().y + (popupBackground.getSize().y - textBounds.height) / 2.0f - 5.0f; // Centrer verticalement
    popupText.setPosition(textOffsetX, textOffsetY);

    // Dessiner les éléments de la popup
    m_window.draw(popupBackground);
    m_window.draw(m_popupSprite);
    m_window.draw(popupText);
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
    case GameState::Infos:
        m_infosBackground->render(m_window);
        m_infoSection->render();
        break;
    case GameState::Custom:
        m_customBackground->render(m_window);
        m_customMenu->render();
        break;

    case GameState::Playing:
        m_playingBackground->render(m_window);
        m_game.get()->render(deltaTime);
        renderPopup(); 
        break;

    case GameState::PlayingInLobby:
        m_playingBackground->render(m_window);
        m_game.get()->render(deltaTime);
        break;

    case GameState::AnimationLevelGame:
    {
        std::cout << "render level game" << std::endl;
        m_levelBackground->render(m_window);
        //m_game.get()->render(deltaTime);
        int l = m_game.get()->getLevelGame();
        renderAnimationNewFile(m_window, m_font, l);
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
            //std::cout << "je suis dans le engine run" << std::endl;
            m_game.get()->run();
        }
        update(deltaTime);
        render(deltaTime);
    }
}
