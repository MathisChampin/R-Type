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
        {sf::Keyboard::Space, false},
        {sf::Keyboard::A, false},
        {sf::Keyboard::Z, false},
        {sf::Keyboard::E, false},
        {sf::Keyboard::R, false},
        {sf::Keyboard::T, false}};

    const std::vector<std::pair<sf::Keyboard::Key, NmpClient::DIRECTION>> directions = {
        {sf::Keyboard::Up, NmpClient::DIRECTION::UP},
        {sf::Keyboard::Down, NmpClient::DIRECTION::DOWN},
        {sf::Keyboard::Left, NmpClient::DIRECTION::LEFT},
        {sf::Keyboard::Right, NmpClient::DIRECTION::RIGHT},
        {sf::Keyboard::Space, NmpClient::DIRECTION::SHOOT},
        {sf::Keyboard::A, NmpClient::DIRECTION::SHOOT1},
        {sf::Keyboard::Z, NmpClient::DIRECTION::SHOOT2},
        {sf::Keyboard::E, NmpClient::DIRECTION::SHOOT3},
        {sf::Keyboard::R, NmpClient::DIRECTION::SHOOT4},
        {sf::Keyboard::T, NmpClient::DIRECTION::SHOOT5}};
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
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
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

    if (currentDirection == nullptr) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            static NmpClient::DIRECTION shoot1 = NmpClient::DIRECTION::SHOOT1;
            currentDirection = &shoot1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            static NmpClient::DIRECTION shoot2 = NmpClient::DIRECTION::SHOOT2;
            currentDirection = &shoot2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            static NmpClient::DIRECTION shoot3 = NmpClient::DIRECTION::SHOOT3;
            currentDirection = &shoot3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            static NmpClient::DIRECTION shoot4 = NmpClient::DIRECTION::SHOOT4;
            currentDirection = &shoot4;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            static NmpClient::DIRECTION shoot5 = NmpClient::DIRECTION::SHOOT5;
            currentDirection = &shoot5;
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

    if (sf::Joystick::isConnected(0)) {
        sf::Joystick::update();
        float xAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float yAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

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

        if (sf::Joystick::isButtonPressed(0, 0)) {
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
        currentDirection = nullptr;
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
