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
    Player(NmpClient::Client &client);
    Player(Player&& other) noexcept
        :
          m_client(other.m_client),
          _id(std::move(other._id))
    {}
    
    ~Player() = default;

    void handleInput();
    void update();
    void render(sf::RenderWindow &window);
    void shoot();

    int get_id() const {
        return _id;
    }

    void updateId(int id) {
        _id = id;
    }
    void sendQueuedMovements();

private:

    NmpClient::Client &m_client;
    int _id;
    std::queue<NmpClient::Packet> m_movementQueue;
    std::mutex m_queueMutex;

    void sendMovementPacket(NmpClient::DIRECTION direction);
};

#endif // PLAYER_HPP
