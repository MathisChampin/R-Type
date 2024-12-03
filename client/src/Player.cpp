#include "../include/Player.hpp"
#include <iostream>

Player::Player(const sf::Vector2f& startPosition, NmpClient::Client& client)
    : m_speed(200.0f), m_currentFrame(0), m_animationTime(0.1f), m_elapsedTime(0.0f), m_client(client)
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
    m_sprite.setPosition(startPosition);
    m_sprite.setOrigin(m_textures[0].getSize().x / 2.0f, m_textures[0].getSize().y / 2.0f);
    m_sprite.setScale(2.0f, 2.0f);
}

void Player::handleInput()
{
    bool moved = false; // Indique si le joueur a bougé

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_sprite.move(0, -m_speed * 0.016f); 
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_sprite.move(0, m_speed * 0.016f); 
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_sprite.move(-m_speed * 0.016f, 0); 
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_sprite.move(m_speed * 0.016f, 0);
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot();
        std::cout << "Pew pew !" << std::endl;
    }

    // Si le joueur a bougé, envoyer la position au serveur
    if (moved) {
        sf::Vector2f position = m_sprite.getPosition();
        std::string message = "move/" + std::to_string(position.x) + "/" + std::to_string(position.y);
        std::vector<uint32_t> buffer;
        m_client.serialize(message, buffer); // Sérialisation de la position
        m_client.send_input(buffer);         // Envoi au serveur
        std::cout << "Position envoyée : " << message << std::endl;
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
}

void Player::shoot()
{
    // Envoi d'un événement de tir au serveur
    std::string message = "shoot";
    std::vector<uint32_t> buffer;
    m_client.serialize(message, buffer);
    m_client.send_input(buffer);
    std::cout << "Action envoyée : " << message << std::endl;
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
