#include "../include/Player.hpp"
#include "../include/client/ClientBinary.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>

Player::Player(int id, const sf::Vector2f& startPosition, NmpClient::Client& client)
    : m_speed(200.0f), m_currentFrame(0), m_animationTime(0.1f), m_elapsedTime(0.0f), m_client(client), m_position(startPosition), _id(id)
{
    for (int i = 1; i <= 5; ++i) {
        sf::Texture texture;
        std::string textureFile = "./assets/player/sprite_" + std::to_string(i) + ".png";
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Erreur : Impossible de charger la texture " << textureFile << std::endl;
            exit(-1);
        }
        m_textures.push_back(texture);
    }

    m_sprite.setTexture(m_textures[m_currentFrame]);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_textures[0].getSize().x / 2.0f, m_textures[0].getSize().y / 2.0f);
    m_sprite.setScale(2.0f, 2.0f);
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

    // Variable pour stocker la direction
    NmpClient::DIRECTION* currentDirection = nullptr;

    // Priorité des directions (haut/bas prioritaire sur gauche/droite)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        static NmpClient::DIRECTION upDirection = NmpClient::DIRECTION::UP;
        currentDirection = &upDirection;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        static NmpClient::DIRECTION downDirection = NmpClient::DIRECTION::DOWN;
        currentDirection = &downDirection;
    }

    // Si pas de direction verticale, on vérifie les directions horizontales
    if (currentDirection == nullptr) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            static NmpClient::DIRECTION leftDirection = NmpClient::DIRECTION::LEFT;
            currentDirection = &leftDirection;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            static NmpClient::DIRECTION rightDirection = NmpClient::DIRECTION::RIGHT;
            currentDirection = &rightDirection;
        }
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

    // S'il y a une direction, on envoie un seul paquet
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
        m_currentFrame = (m_currentFrame + 1) % m_textures.size();
        m_sprite.setTexture(m_textures[m_currentFrame]);
    }
    sendQueuedMovements();
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Player::sendMovementPacket(NmpClient::DIRECTION direction)
{
    NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, direction);
    std::vector<uint32_t> buffer;
    NmpBinary::Binary binary;
    binary.serialize(packet, buffer);
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
