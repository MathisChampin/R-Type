#include "../include/Player.hpp"
#include "../include/client/ClientBinary.hpp"
#include <iostream>
#include <algorithm>

Player::Player(const sf::Vector2f& startPosition, NmpClient::Client& client)
    : m_speed(200.0f), m_currentFrame(0), m_animationTime(0.1f), m_elapsedTime(0.0f), m_client(client), m_bulletTexture()
{
    for (int i = 1; i <= 5; ++i) {
        sf::Texture texture;
        std::string textureFile = "./assets/player/sprite_" + std::to_string(i) + ".png";
        if (!texture.loadFromFile(textureFile)) {
            exit(-1);
        }
        m_textures.push_back(texture);
    }

    if (!m_bulletTexture.loadFromFile("./assets/player/bullet.png")) {
        exit(-1);
    }

    // // Charger le son de tir une seule fois
    // if (!shootSound.openFromFile("./assets/player/gun.mp3")) {
    //     std::cerr << "Erreur : Impossible de charger le son du tir" << std::endl;
    //     exit(-1);
    // }

    m_sprite.setTexture(m_textures[m_currentFrame]);
    m_sprite.setPosition(startPosition);
    m_sprite.setOrigin(m_textures[0].getSize().x / 2.0f, m_textures[0].getSize().y / 2.0f);
    m_sprite.setScale(2.0f, 2.0f);
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_sprite.move(0, -m_speed * 0.016f); 
        NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, NmpClient::DIRECTION::UP);

        std::vector<uint32_t> buffer;
        NmpBinary::Binary binary;
        binary.serialize(packet, buffer);

        m_client.send_input(packet);
        std::cout << "Position Up envoyé" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_sprite.move(0, m_speed * 0.016f); 

        NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, NmpClient::DIRECTION::DOWN);

        std::vector<uint32_t> buffer;
        NmpBinary::Binary binary;
        binary.serialize(packet, buffer);

        m_client.send_input(packet);
        std::cout << "Position Down envoyé" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_sprite.move(-m_speed * 0.016f, 0);
        NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, NmpClient::DIRECTION::LEFT);

        std::vector<uint32_t> buffer;
        NmpBinary::Binary binary;
        binary.serialize(packet, buffer);

        m_client.send_input(packet);
        std::cout << "Position Left envoyé" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_sprite.move(m_speed * 0.016f, 0);
        NmpClient::Packet packet(m_client.get_id(), NmpClient::EVENT::MOVE, NmpClient::DIRECTION::RIGHT);

        std::vector<uint32_t> buffer;
        NmpBinary::Binary binary;
        binary.serialize(packet, buffer);

        m_client.send_input(packet);
        std::cout << "Position Right envoyé" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot();
        std::cout << "Pew pew !" << std::endl;
    }
}

void Player::update(float deltaTime)
{
    m_elapsedTime += deltaTime;

    // Animation du joueur
    if (m_elapsedTime >= m_animationTime) {
        m_elapsedTime = 0.0f;
        m_currentFrame = (m_currentFrame + 1) % m_textures.size();
        m_sprite.setTexture(m_textures[m_currentFrame]);
    }

    for (auto& bullet : m_bullets) {
        bullet.move(300.0f * deltaTime, 0); 
    }

    // m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const sf::Sprite& bullet) {
    // }), m_bullets.end());
}

void Player::shoot()
{
    sf::Sprite bullet;
    bullet.setTexture(m_bulletTexture);
    bullet.setPosition(m_sprite.getPosition()- sf::Vector2f(0, 50));
    bullet.setOrigin(((m_bulletTexture.getSize().x / 2.0f) - 900), (m_bulletTexture.getSize().y - 1100));
    bullet.setScale(0.1f, 0.1f);
    m_bullets.push_back(bullet);

    // shootSound.play(); // Joue le son ici

    std::cout << "Nombre de bullets : " << m_bullets.size() << std::endl;

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
