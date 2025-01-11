#ifndef SHOOT_HPP
#define SHOOT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Shoot
{
public:
    /**
     * @brief Constructs a Shoot object with the given ID and starting position.
     *
     * @param id The unique identifier for the shoot.
     * @param startPosition The initial position of the shoot in 2D space.
     */
    Shoot(int id, const sf::Vector2f &startPosition);

    /**
     * @brief Updates the shoot's position based on the elapsed time.
     *
     * @param deltaTime The time elapsed since the last update.
     */
    void render(sf::RenderWindow &window);

    /**
     * @brief Updates the shoot's position.
     *
     * @param position The new position of the shoot.
     */
    void updatePosition(const sf::Vector2f &position)
    {
        m_position = position;
        m_shape.setPosition(m_position);
    }

    int get_id() const
    {
        return _id;
    };

    sf::Vector2f getPosition() const { return m_position; };

private:
    sf::CircleShape m_shape;
    int _id;
    sf::Vector2f m_position;
};

#endif // SHOOT_HPP
