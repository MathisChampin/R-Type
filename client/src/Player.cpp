#include "../include/Player.hpp"
#include "../include/client/ClientBinary.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>

Player::Player(int id, const sf::Vector2f& startPosition, NmpClient::Client& client, const std::string& configPath)
    : m_sprite(configPath), // Initialiser m_sprite en premier car il est déclaré en premier dans la classe
      m_speed(200.0f), 
      m_currentFrame(0), 
      m_animationTime(0.1f), 
      m_elapsedTime(0.0f), 
      m_client(client), 
      m_position(startPosition),
      _id(id) // _id en dernier car il est déclaré en dernier dans la classe
{
    m_sprite.setPosition(m_position);
}

void Player::handleInput()
{
    static std::map<sf::Keyboard::Key, bool> keyStates = {
        {sf::Keyboard::Up, false},
        {sf::Keyboard::Down, false},
        {sf::Keyboard::Left, false},
        {sf::Keyboard::Right, false},
        {sf::Keyboard::Space, false}
    };

    const std::vector<std::pair<sf::Keyboard::Key, NmpClient::DIRECTION>> directions = {
        {sf::Keyboard::Up, NmpClient::DIRECTION::UP},
        {sf::Keyboard::Down, NmpClient::DIRECTION::DOWN},
        {sf::Keyboard::Left, NmpClient::DIRECTION::LEFT},
        {sf::Keyboard::Right, NmpClient::DIRECTION::RIGHT},
        {sf::Keyboard::Space, NmpClient::DIRECTION::SHOOT}
    };

    NmpClient::DIRECTION* currentDirection = nullptr;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        static NmpClient::DIRECTION upDirection = NmpClient::DIRECTION::UP;
        currentDirection = &upDirection;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        static NmpClient::DIRECTION downDirection = NmpClient::DIRECTION::DOWN;
        currentDirection = &downDirection;
    }

    if (currentDirection == nullptr) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            static NmpClient::DIRECTION leftDirection = NmpClient::DIRECTION::LEFT;
            currentDirection = &leftDirection;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            static NmpClient::DIRECTION rightDirection = NmpClient::DIRECTION::RIGHT;
            currentDirection = &rightDirection;
        }
    }

    bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    if (isSpacePressed && !keyStates[sf::Keyboard::Space]) {
        static NmpClient::DIRECTION spaceDirection = NmpClient::DIRECTION::SHOOT;
        currentDirection = &spaceDirection;
    }
    for (auto& [key, state] : keyStates) {
        state = sf::Keyboard::isKeyPressed(key);
    }

    if (currentDirection != nullptr) {
        NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, *currentDirection);
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_movementQueue.push(packet);
        }
        std::cout << "Key pressed: " << static_cast<int>(*currentDirection) << std::endl;
        sendQueuedMovements();
    }
}

void Player::update(float deltaTime)
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime >= m_animationTime) {
        m_elapsedTime = 0.0f;
        m_currentFrame = (m_currentFrame + 1) % 4; // Exemple: 4 frames
        m_sprite.setTextureRect(sf::IntRect(m_currentFrame * 32, 0, 32, 32)); // Exemple: largeur de frame 32
    }
    sendQueuedMovements();
}

void Player::render(sf::RenderWindow& window)
{
    m_sprite.draw(window);
}

void Player::shoot()
{
    // Implémentez la logique de tir ici
    std::cout << "Player " << _id << " is shooting!" << std::endl;
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
    while (!m_movementQueue.empty()) {
        NmpClient::Packet packet = m_movementQueue.front();

        if (packet.getDirection().has_value()) {
            std::cout << "Sending packet with direction: " << static_cast<int>(packet.getDirection().value()) << std::endl;
        } else {
            std::cout << "Sending packet with no direction" << std::endl;
        }
        m_client.send_input(packet);
        m_movementQueue.pop();
    }
}