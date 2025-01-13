#include "../include/Score.hpp"
#include <iostream>

Score::Score() : m_currentScore(0) {}

Score::~Score() {}

void Score::initialize(const sf::Font &font, unsigned int characterSize, const sf::Vector2f &position)
{
    m_scoreText.setFont(font);
    m_scoreText.setCharacterSize(characterSize);
    m_scoreText.setPosition(position);
    m_scoreText.setFillColor(sf::Color::White);
    updateScore(0);
}

void Score::updateScore(int newScore) {
    if (newScore < 0) {
        std::cerr << "Error: Score cannot be negative!" << std::endl;
        return;
    }

    if (newScore == m_currentScore) {
        return;
    }

    m_currentScore = newScore;
    m_scoreText.setString("Score: " + std::to_string(m_currentScore));

    sf::FloatRect textRect = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(textRect.width, 0);
    m_scoreText.setPosition(sf::Vector2f(1920 - 10, m_scoreText.getPosition().y));
}


void Score::render(sf::RenderWindow &window)
{
    window.draw(m_scoreText);
}
