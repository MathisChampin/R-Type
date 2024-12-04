#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../include/client/Client.hpp"

class Player {
public:
    Player(const sf::Vector2f& startPosition, NmpClient::Client& client);

    void handleInput();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void shoot();

private:
    sf::Sprite m_sprite;                       
    std::vector<sf::Texture> m_textures;        
    float m_speed;                              

    int m_currentFrame;                          
    float m_animationTime;                       
    float m_elapsedTime;                         

    NmpClient::Client& m_client;

    void loadTexture(const std::string& textureFile);
};

#endif // PLAYER_HPP
