#include "../include/Level.hpp"
#include <iostream>

Level::Level() : m_currentLevel(0) {}

Level::~Level() {}

void Level::initialize(const sf::Font &font, unsigned int characterSize, const sf::Vector2f &position)
{
    m_levelText.setFont(font);
    m_levelText.setCharacterSize(characterSize);
    m_levelText.setPosition(position);
    m_levelText.setFillColor(sf::Color::White);

    m_currentLevel = 0;
    m_levelText.setString("Level: 0");

    sf::FloatRect textRect = m_levelText.getLocalBounds();
    m_levelText.setOrigin(textRect.width, 0);
    m_levelText.setPosition(sf::Vector2f(1920 - 500, position.y));
}


void Level::updateLevel(int newLevel) {
    if (newLevel < 0) {
        std::cerr << "Error: Score cannot be negative!" << std::endl;
        return;
    }

    if (newLevel == m_currentLevel) {
        return;
    }

    m_currentLevel = newLevel;
    m_levelText.setString("Level: " + std::to_string(m_currentLevel));

    sf::FloatRect textRect = m_levelText.getLocalBounds();
    m_levelText.setOrigin(textRect.width, 0);
    m_levelText.setPosition(sf::Vector2f(1920 - 500, m_levelText.getPosition().y));
}

void Level::render(sf::RenderWindow &window)
{
    window.draw(m_levelText);
}
