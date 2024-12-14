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
    Player(const sf::Vector2f &startPosition, NmpClient::Client &client);

    void handleInput();
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    void shoot();
    void sendQueuedMovements();

private:
    sf::Sprite m_sprite;
    std::vector<sf::Texture> m_textures;
    std::vector<sf::Sprite> m_bullets;
    float m_speed;
    int m_currentFrame;
    float m_animationTime;
    float m_elapsedTime;

    NmpClient::Client &m_client;
    sf::Texture m_bulletTexture;
    std::queue<NmpClient::Packet> m_movementQueue;
    std::mutex m_queueMutex;

    void sendMovementPacket(NmpClient::DIRECTION direction);
    void loadTexture(const std::string &textureFile);
};

#endif // PLAYER_HPP
