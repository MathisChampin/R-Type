#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../include/client/Sprite.hpp"

class Enemy {
public:
    Enemy(int id, const sf::Vector2f& startPosition, const std::string& configPath);

    void render(sf::RenderWindow& window);
    void update(float deltaTime);

    int get_id() const { return _id; };

    void updatePosition(const sf::Vector2f& position) {
        m_position = position;
        m_sprite.setPosition(m_position);
    }

    sf::Vector2f getPosition() const { return m_position; };

    Enemy(const Enemy&) = delete;             // Supprimer le constructeur de copie
    Enemy& operator=(const Enemy&) = delete;  // Supprimer l'opérateur d'affectation de copie
private:
    int _id;
    sf::Vector2f m_position;
    Sprite m_sprite;
    int m_currentFrame = 0;
    float m_animationTime = 0.1f;
    float m_elapsedTime = 0.0f;
};

#endif // ENEMY_HPP