// CustomMenu.cpp
#include "CustomMenu.hpp"
#include <iostream>

CustomMenu::CustomMenu(sf::RenderWindow& window)
    : m_window(window), m_selectedSkinIndex(0) {
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf")) {
        std::cout << "Erreur : Impossible de charger la police" << std::endl;
    }

    setupTitleText();
    setupSkins();
    loadSkinTextures();
}

void CustomMenu::setupTitleText() {
    m_titleText.setFont(m_font);
    m_titleText.setString("Select Skin");
    m_titleText.setCharacterSize(90);
    m_titleText.setFillColor(sf::Color::Blue);

    sf::FloatRect textRect = m_titleText.getLocalBounds();
    m_titleText.setOrigin(textRect.left + textRect.width / 2.0f, 
                         textRect.top + textRect.height / 2.0f);
    m_titleText.setPosition(900, 100);
}

void CustomMenu::setupSkins() {
    m_skins = {"Skin1", "Skin2", "Skin3", "Skin4", "Skin5", "Skin6"};
    m_skinText.setFont(m_font);
    m_skinText.setCharacterSize(50);
    m_skinText.setFillColor(sf::Color::White);
    updateSkinText();
}

void CustomMenu::loadSkinTextures() {
    std::vector<std::string> skinPaths = {
        "./assets/skins/sprite_0_0.png",
        "./assets/skins/sprite_1_0.png",
        "./assets/skins/sprite_2_0.png",
        "./assets/skins/sprite_3_0.png",
        "./assets/skins/sprite_4_0.png",
    };

    m_skinTextures.resize(skinPaths.size());
    m_skinSprites.resize(skinPaths.size());

    for (size_t i = 0; i < skinPaths.size(); ++i) {
        if (!m_skinTextures[i].loadFromFile(skinPaths[i])) {
            std::cerr << "Erreur : Impossible de charger " << skinPaths[i] << std::endl;
            continue;
        }

        m_skinSprites[i].setTexture(m_skinTextures[i]);
        m_skinSprites[i].setScale(SPRITE_SCALE, SPRITE_SCALE);

        // Positionner les sprites en ligne horizontale
        float spriteWidth = m_skinSprites[i].getGlobalBounds().width;
        // float totalWidth = spriteWidth * skinPaths.size();
        // float startX = (m_window.getSize().x - totalWidth) / 2.0f;
        // float y = m_window.getSize().y / 2.0f;

        float startX = 500;
        float y = 500;

        m_skinSprites[i].setPosition(startX + i * spriteWidth, y);
    }
}

void CustomMenu::updateSkinText() {
    m_skinText.setString("Selected Skin: " + m_skins[m_selectedSkinIndex]);
    sf::FloatRect textRect = m_skinText.getLocalBounds();
    m_skinText.setOrigin(textRect.left + textRect.width / 2.0f, 
                        textRect.top + textRect.height / 2.0f);
    m_skinText.setPosition(900, 200);
}

void CustomMenu::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            m_selectedSkinIndex = (m_selectedSkinIndex - 1 + m_skins.size()) % m_skins.size();
            updateSkinText();
        }
        else if (event.key.code == sf::Keyboard::Right) {
            m_selectedSkinIndex = (m_selectedSkinIndex + 1) % m_skins.size();
            updateSkinText();
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            
            // Vérifier si un sprite a été cliqué
            for (size_t i = 0; i < m_skinSprites.size(); ++i) {
                if (m_skinSprites[i].getGlobalBounds().contains(mousePos)) {
                    m_selectedSkinIndex = i;
                    updateSkinText();
                    break;
                }
            }
        }
    }
}

void CustomMenu::update() {
}

void CustomMenu::render() {
    m_window.draw(m_titleText);
    
    // Dessiner tous les sprites
    for (size_t i = 0; i < m_skinSprites.size(); ++i) {
        // Mettre en surbrillance le skin sélectionné
        if (i == m_selectedSkinIndex) {
            m_skinSprites[i].setColor(sf::Color(255, 255, 255, 255));
        } else {
            m_skinSprites[i].setColor(sf::Color(128, 128, 128, 255));
        }
        m_window.draw(m_skinSprites[i]);
    }
    
    m_window.draw(m_skinText);
}