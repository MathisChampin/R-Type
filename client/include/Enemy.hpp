#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../include/client/Sprite.hpp"

class Enemy
{
public:
    /**
     * @brief Constructs an Enemy object with the given ID, starting position, and configuration path.
     *
     * @param id The unique identifier for the enemy.
     * @param startPosition The initial position of the enemy in the game world.
     * @param configPath The file path to the enemy's configuration file.
     */
    Enemy(int id, const sf::Vector2f &startPosition, const std::string &configPath);

    /**
     * @brief Draws the enemy sprite onto the given render window.
     *
     * @param window The render window where the enemy sprite will be drawn.
     */
    void render(sf::RenderWindow &window);

    /**
     * @brief Updates the enemy's animation based on the elapsed time.
     *
     * @param deltaTime The time elapsed since the last update.
     */
    void update(float deltaTime);

    /**
     * @brief Updates the enemy's position.
     *
     * @param position The new position of the enemy.
     */
    void updatePosition(const sf::Vector2f &position)
    {
        m_position = position;
        m_sprite.setPosition(m_position);
    }

    int get_id() const { return _id; };
    sf::Vector2f getPosition() const { return m_position; };
    void updateId(int id) { _id = id; }

private:
    int _id;
    sf::Vector2f m_position;
    Sprite m_sprite;
    int m_currentFrame = 0;
    float m_animationTime = 0.1f;
    float m_elapsedTime = 0.0f;
};

#endif // ENEMY_HPP