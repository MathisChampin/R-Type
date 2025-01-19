#include "../include/Level.hpp"
#include <iostream>

Level::Level() : m_currentLevel(0) {}

Level::~Level() {}

void Level::initialize(const sf::Font &font, unsigned int characterSize, const sf::Vector2f &position)
{
    m_levelText.setFont(font);
    m_levelText.setCharacterSize(characterSize);
    m_levelText.setFillColor(sf::Color::White);
    m_currentLevel = 0;
    m_levelText.setString("Level: 0");

    sf::FloatRect textRect = m_levelText.getLocalBounds();
    m_levelText.setOrigin(textRect.width, 0);

    float leftOffset = 100.0f;
    m_levelText.setPosition(sf::Vector2f(1920 - 500 - leftOffset, position.y));

    m_backgroundRect.setFillColor(sf::Color(0, 0, 0, 200));
    m_backgroundRect.setOutlineColor(sf::Color::White);
    m_backgroundRect.setOutlineThickness(2.0f);
    updateBackground();
}

void Level::updateLevel(int newLevel)
{
    if (newLevel < 0) {
        std::cerr << "Error: Level cannot be negative!" << std::endl;
        return;
    }

    if (newLevel == m_currentLevel) {
        return;
    }

    m_currentLevel = newLevel;
    m_levelText.setString("Level: " + std::to_string(m_currentLevel));

    updateBackground();
}

void Level::updateBackground()
{
    sf::FloatRect textRect = m_levelText.getLocalBounds();
    m_levelText.setOrigin(textRect.width, 0);

    float extraWidth = -10.0f;
    float extraHeight = 15.0f;
    m_backgroundRect.setSize(sf::Vector2f(textRect.width + 20 + extraWidth, textRect.height + 10 + extraHeight));

    m_backgroundRect.setOrigin(m_backgroundRect.getSize().x, 0);
    m_backgroundRect.setPosition(m_levelText.getPosition().x, m_levelText.getPosition().y - 5);
}

void Level::render(sf::RenderWindow &window)
{
    window.draw(m_backgroundRect);
    window.draw(m_levelText);
}
