#ifndef SHOOT_HPP
#define SHOOT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Shoot
{
public:
    Shoot(int id, const sf::Vector2f &startPosition);

    void render(sf::RenderWindow &window);

    int get_id() const {
        return _id;
    };

    void updatePosition(const sf::Vector2f &position) {
        m_position = position;
        m_shape.setPosition(m_position);
    }

    sf::Vector2f getPosition() const { return m_position; };

private:
    sf::CircleShape m_shape;
    int _id;                        
    sf::Vector2f m_position;        
};

#endif // SHOOT_HPP
