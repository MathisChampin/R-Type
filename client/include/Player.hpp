#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include "../include/client/Client.hpp"

class Player
{
public:
    Player(int id, const sf::Vector2f &startPosition, NmpClient::Client &client);
    Player(Player&& other) noexcept
        : m_sprite(std::move(other.m_sprite)), 
          m_textures(std::move(other.m_textures)),
          m_speed(other.m_speed),
          m_currentFrame(other.m_currentFrame),
          m_animationTime(other.m_animationTime),
          m_elapsedTime(other.m_elapsedTime),
          m_client(other.m_client),
          m_position(std::move(other.m_position)),
          _id(std::move(other._id))
    {}
    
    ~Player() = default;

    void handleInput();
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    void shoot();
    int get_id() const {
        return _id;
    };
    void updatePosition(const sf::Vector2f &position) {
        m_sprite.setPosition(position.x, position.y);
    }
    void updateId(int id) {
        _id = id;
    }
    void sendQueuedMovements();
    sf::Vector2f getPosition() const { return m_position; };

private:
    sf::Sprite m_sprite;
    std::vector<sf::Texture> m_textures;
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
    void loadTexture(const std::string &textureFile);
};

#endif // PLAYER_HPP
