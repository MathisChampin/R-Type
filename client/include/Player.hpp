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
    Player(NmpClient::Client &client);
    ~Player() = default;
    
    void updateId(int id) { _id = id; }
    void sendQueuedMovements();
    void handleInput();
    int get_id() const { return _id; };
    Player &operator=(const Player &) = delete;
    void sendMovementPacket(NmpClient::DIRECTION direction);

private:

    NmpClient::Client &m_client;
    int _id;
    std::queue<NmpClient::Packet> m_movementQueue;
    std::mutex m_queueMutex;

};

#endif // PLAYER_HPP