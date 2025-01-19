#include "../include/Score.hpp"
#include <iostream>

Score::Score() : m_currentScore(0) {}

Score::~Score() {}

void Score::initialize(const sf::Font &font, unsigned int characterSize, const sf::Vector2f &position)
{
    m_scoreText.setFont(font);
    m_scoreText.setCharacterSize(characterSize);
    m_scoreText.setFillColor(sf::Color::White);
    m_currentScore = 0;
    m_scoreText.setString("Score: 0");

    sf::FloatRect textRect = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(textRect.width, 0);
    m_scoreText.setPosition(sf::Vector2f(1920 - 20, position.y));

    m_backgroundRect.setFillColor(sf::Color(0, 0, 0, 200));
    m_backgroundRect.setOutlineColor(sf::Color::White);
    m_backgroundRect.setOutlineThickness(2.0f);
    updateBackground();
}

void Score::updateScore(int newScore)
{
    if (newScore < 0) {
        std::cerr << "Error: Score cannot be negative!" << std::endl;
        return;
    }

    if (newScore == m_currentScore) {
        return;
    }

    m_currentScore = newScore;
    m_scoreText.setString("Score: " + std::to_string(m_currentScore));

    updateBackground();
}

void Score::updateBackground()
{
    sf::FloatRect textRect = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(textRect.width, 0);
    m_scoreText.setPosition(sf::Vector2f(1920 - 20, m_scoreText.getPosition().y));

    float extraWidth = -10.0f;
    float extraHeight = 15.0f;
    m_backgroundRect.setSize(sf::Vector2f(textRect.width + 20 + extraWidth, textRect.height + 10 + extraHeight));

    m_backgroundRect.setOrigin(m_backgroundRect.getSize().x, 0);
    m_backgroundRect.setPosition(m_scoreText.getPosition().x, m_scoreText.getPosition().y - 5);
}


void Score::render(sf::RenderWindow &window)
{
    window.draw(m_backgroundRect);
    window.draw(m_scoreText);
}
