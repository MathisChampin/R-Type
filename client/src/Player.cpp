#include "../include/Player.hpp"
#include "../include/client/ClientBinary.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>

Player::Player( NmpClient::Client& client)
    : m_client(client)
{
}

void Player::handleInput()
{
    static std::map<sf::Keyboard::Key, bool> keyStates = {
        {sf::Keyboard::Up, false},
        {sf::Keyboard::Down, false},
        {sf::Keyboard::Left, false},
        {sf::Keyboard::Right, false},
        {sf::Keyboard::Space, false}};

    const std::vector<std::pair<sf::Keyboard::Key, NmpClient::DIRECTION>> directions = {
        {sf::Keyboard::Up, NmpClient::DIRECTION::UP},
        {sf::Keyboard::Down, NmpClient::DIRECTION::DOWN},
        {sf::Keyboard::Left, NmpClient::DIRECTION::LEFT},
        {sf::Keyboard::Right, NmpClient::DIRECTION::RIGHT},
        {sf::Keyboard::Space, NmpClient::DIRECTION::SHOOT}};
    /**
     * @brief Updates the player's animation based on the elapsed time.
     *
     * @param deltaTime The time elapsed since the last update.
     */
    void update(float deltaTime);
    NmpClient::DIRECTION *currentDirection = nullptr;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        static NmpClient::DIRECTION upDirection = NmpClient::DIRECTION::UP;
        currentDirection = &upDirection;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        static NmpClient::DIRECTION downDirection = NmpClient::DIRECTION::DOWN;
        currentDirection = &downDirection;
    }

    if (currentDirection == nullptr)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            static NmpClient::DIRECTION leftDirection = NmpClient::DIRECTION::LEFT;
            currentDirection = &leftDirection;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            static NmpClient::DIRECTION rightDirection = NmpClient::DIRECTION::RIGHT;
            currentDirection = &rightDirection;
        }
    }

    bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    if (isSpacePressed && !keyStates[sf::Keyboard::Space])
    {
        static NmpClient::DIRECTION spaceDirection = NmpClient::DIRECTION::SHOOT;
        currentDirection = &spaceDirection;
    }
    for (auto &[key, state] : keyStates)
    {
        state = sf::Keyboard::isKeyPressed(key);
    }

    // Ajout : Gestion de la manette
    if (sf::Joystick::isConnected(0)) {
        sf::Joystick::update();
        float xAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::X); // Axe horizontal
        float yAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Y); // Axe vertical

        if (yAxis < -50) {
            static NmpClient::DIRECTION upDirection = NmpClient::DIRECTION::UP;
            currentDirection = &upDirection;
        } else if (yAxis > 50) {
            static NmpClient::DIRECTION downDirection = NmpClient::DIRECTION::DOWN;
            currentDirection = &downDirection;
        } else if (xAxis < -50) {
            static NmpClient::DIRECTION leftDirection = NmpClient::DIRECTION::LEFT;
            currentDirection = &leftDirection;
        } else if (xAxis > 50) {
            static NmpClient::DIRECTION rightDirection = NmpClient::DIRECTION::RIGHT;
            currentDirection = &rightDirection;
        }

        // Bouton pour tirer
        if (sf::Joystick::isButtonPressed(0, 0)) { // Bouton 0 pour tirer
            static NmpClient::DIRECTION shootDirection = NmpClient::DIRECTION::SHOOT;
            currentDirection = &shootDirection;
        }
    }

    if (currentDirection != nullptr)
    {
        NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, *currentDirection);
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_movementQueue.push(packet);
        }
        //m_client.send_input(packet);
        std::cout << "Key pressed: " << static_cast<int>(*currentDirection) << std::endl;
        sendQueuedMovements();
    }
}

void Player::sendMovementPacket(NmpClient::DIRECTION direction)
{
    NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, direction);
    m_client.send_input(packet);
    std::cout << "Position " << static_cast<int>(direction) << " envoyée" << std::endl;
}

void Player::sendQueuedMovements()
{
    std::lock_guard<std::mutex> lock(m_queueMutex);
    while (!m_movementQueue.empty())
    {
        NmpClient::Packet packet = m_movementQueue.front();

        if (packet.getDirection().has_value())
        {
            std::cout << "Sending packet with direction: " << static_cast<int>(packet.getDirection().value()) << std::endl;
        }
        else
        {
            std::cout << "Sending packet with no direction" << std::endl;
        }
        m_client.send_input(packet);
        m_movementQueue.pop();
    }
}
