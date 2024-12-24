#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include "../include/client/Client.hpp"
#include "../include/client/Sprite.hpp"

class Player {
public:
    Player(int id, const sf::Vector2f& startPosition, NmpClient::Client& client, const std::string& configPath);
    ~Player() = default;

    void handleInput();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void shoot();
    int get_id() const { return _id; };
    void updatePosition(const sf::Vector2f& position) {
        m_position.x = position.x;
        m_position.y = position.y;
    };

    void updateId(int id) { _id = id; }
    void sendQueuedMovements();
    sf::Vector2f getPosition() const { return m_position; }

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

private:
    Sprite m_sprite;
    float m_speed;
    int m_currentFrame;
    float m_animationTime;
    float m_elapsedTime;

    NmpClient::Client& m_client;
    sf::Vector2f m_position;
    int _id;
    std::queue<NmpClient::Packet> m_movementQueue;
    std::mutex m_queueMutex;

    void sendMovementPacket(NmpClient::DIRECTION direction);
};

#endif // PLAYER_HPP