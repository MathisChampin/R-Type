#include "Enemy.hpp"

Enemy::Enemy(int id, const sf::Vector2f& startPosition, const std::string& configPath)
    : _id(id), m_position(startPosition), m_sprite(configPath)
{
    m_sprite.setPosition(m_position);
}

void Enemy::render(sf::RenderWindow& window)
{
    m_sprite.draw(window);
}

void Enemy::update(float deltaTime)
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime >= m_animationTime) {
        m_elapsedTime = 0.0f;
        m_currentFrame = (m_currentFrame + 1) % 4; // Exemple: 4 frames
        m_sprite.setTextureRect(sf::IntRect(m_currentFrame * 32, 0, 32, 32)); // Exemple: largeur de frame 32
    }
}