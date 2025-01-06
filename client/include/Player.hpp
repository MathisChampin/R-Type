#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include "../include/client/Client.hpp"
#include "../include/client/Sprite.hpp"

class Player
{
public:
    /**
     * @brief Constructs a new Player object.
     *
     * @param id The unique identifier for the player.
     * @param startPosition The starting position of the player in the game world.
     * @param client Reference to the NmpClient::Client object for network communication.
     * @param configPath The path to the configuration file for the player.
     */
    Player(int id, const sf::Vector2f &startPosition, NmpClient::Client &client, const std::string &configPath);
    Player(const Player &) = delete;
    ~Player() = default;

    /**
     * @brief Updates the player's animation based on the elapsed time.
     *
     * @param deltaTime The time elapsed since the last update.
     */
    void update(float deltaTime);

    /**
     * @brief Draws the player sprite onto the given render window.
     *
     * @param window The render window where the player sprite will be drawn.
     */
    void render(sf::RenderWindow &window);

    /**
     * @brief Updates the player's position.
     *
     * @param position The new position of the player.
     */
    void updatePosition(const sf::Vector2f &position)
    {
        m_position.x = position.x;
        m_position.y = position.y;
    };

    void updateId(int id) { _id = id; }
    void sendQueuedMovements();
    sf::Vector2f getPosition() const { return m_position; }
    void handleInput();
    int get_id() const { return _id; };
    Player &operator=(const Player &) = delete;

private:
    Sprite m_sprite;
    float m_speed;
    int m_currentFrame;
    float m_animationTime;
    float m_elapsedTime;

    NmpClient::Client &m_client;
    sf::Vector2f m_position;
    int _id;
    std::queue<NmpClient::Packet> m_movementQueue;
    std::mutex m_queueMutex;

    void sendMovementPacket(NmpClient::DIRECTION direction);
};

#endif // PLAYER_HPP