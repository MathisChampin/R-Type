#include "../include/Enemy.hpp"
#include <iostream>

Enemy::Enemy(int id, const sf::Vector2f &startPosition)
    : m_speed(100.0f), m_currentFrame(0), m_animationTime(0.1f), 
      m_elapsedTime(0.0f), m_direction(1), _id(id), m_position(startPosition)
{
    for (int i = 1; i <= 7; ++i) {
        sf::Texture texture;
        std::string textureFile = "./assets/enemy/sprite_" + std::to_string(i) + ".png";
        if (!texture.loadFromFile(textureFile)) {
            exit(-1);
        }
        m_textures.push_back(texture);
    }

    m_sprite.setTexture(m_textures[m_currentFrame]);
    std::cout << "Enemy posx = " << m_position.x << " posy = " << m_position.y << std::endl;
    m_sprite.setPosition(m_position);
    m_sprite.setScale(2.0f, 2.0f);
}

void Enemy::update(float deltaTime)
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime >= m_animationTime) {
        m_elapsedTime = 0.0f;
        m_currentFrame = (m_currentFrame + 1) % m_textures.size();
        m_sprite.setTexture(m_textures[m_currentFrame]);
    }

    m_sprite.move(0, m_speed * deltaTime * m_direction);

    // Changement de direction si le sprite atteint les bords de l'écran
    if (m_sprite.getPosition().y <= 0 || m_sprite.getPosition().y + m_sprite.getGlobalBounds().height >= 600) {
        m_direction *= -1;
    }
}

void Enemy::render(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}
