#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Enemy
{
public:
    Enemy(int id, const sf::Vector2f &startPosition);
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    int get_id() const {
        return _id;
    };
    void updatePosition(const sf::Vector2f &position) {
        m_sprite.setPosition(position.x, position.y);
    }
    void updateId(int id) {
        _id = id;
    }
    sf::Vector2f getPosition() const { return m_position; };

private:
    sf::Sprite m_sprite;
    std::vector<sf::Texture> m_textures;
    float m_speed;
    int m_currentFrame;
    float m_animationTime;
    float m_elapsedTime;
    int m_direction;
    int _id;
    sf::Vector2f m_position;
    void loadTexture(const std::string &textureFile);
};

#endif // ENEMY_HPP
