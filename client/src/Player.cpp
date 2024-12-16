#include "../include/Player.hpp"
#include "../include/client/ClientBinary.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>

Player::Player(int id, const sf::Vector2f& startPosition, NmpClient::Client& client)
    : m_speed(200.0f), m_currentFrame(0), m_animationTime(0.1f), m_elapsedTime(0.0f), m_client(client), m_bulletTexture(), m_position(startPosition), _id(id)
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

    if (!m_bulletTexture.loadFromFile("./assets/player/bullet.png")) {
        std::cerr << "Erreur : Impossible de charger la texture bullet.png" << std::endl;
        exit(-1);
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
        {sf::Keyboard::Right, NmpClient::DIRECTION::RIGHT}
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

    // S'il y a une direction, on envoie un seul paquet
    if (currentDirection != nullptr) {
        NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, *currentDirection);
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_movementQueue.push(packet);
        }
        std::cout << "Key pressed: " << static_cast<int>(*currentDirection) << std::endl;
        sendQueuedMovements();

        // Mettre à jour la position du sprite avec les nouvelles données
        NmpClient::Packet newData = m_client.get_data();
        m_sprite.setPosition(newData.getX(), newData.getY());
    }
    // Gestion du tir
    static sf::Clock shootClock;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (shootClock.getElapsedTime().asSeconds() >= 0.2f) {
            shoot();
            std::cout << "Pew pew !" << std::endl;
            shootClock.restart();
        }
        keyStates[sf::Keyboard::Space] = true;
    } else {
        keyStates[sf::Keyboard::Space] = false;
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

    for (auto& bullet : m_bullets) {
        bullet.move(300.0f * deltaTime, 0);
    }

    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const sf::Sprite& bullet) {
        return bullet.getPosition().x > 800 || bullet.getPosition().x < 0 ||
               bullet.getPosition().y > 600 || bullet.getPosition().y < 0;
    }), m_bullets.end());
    sendQueuedMovements();
}

void Player::shoot()
{
    sf::Sprite bullet;
    bullet.setTexture(m_bulletTexture);
    bullet.setPosition(m_sprite.getPosition() - sf::Vector2f(0, 50));
    bullet.setOrigin(((m_bulletTexture.getSize().x / 2.0f) - 900), (m_bulletTexture.getSize().y - 1100));
    bullet.setScale(0.1f, 0.1f);
    m_bullets.push_back(bullet);

    NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::SHOOT);
    std::vector<uint32_t> buffer;
    NmpBinary::Binary binary;
    binary.serialize(packet, buffer);
    m_client.send_input(packet);
    std::cout << "Action de tir envoyée" << std::endl;
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
    for (const auto& bullet : m_bullets) {
        window.draw(bullet);
    }
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
