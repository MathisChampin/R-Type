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
    updateScore(0); // Initialise avec un score de 0
}

void Score::updateScore(int newScore)
{
    m_currentScore = newScore;
    m_scoreText.setString("Score: " + std::to_string(m_currentScore));
    // Adjust the position to the right side of the screen
    sf::FloatRect textRect = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(textRect.width, 0);
    m_scoreText.setPosition(sf::Vector2f(1920 - 10, m_scoreText.getPosition().y)); // Assuming a 1920 width screen and 10 pixels padding
}

void Score::render(sf::RenderWindow &window)
{
    window.draw(m_scoreText);
}
