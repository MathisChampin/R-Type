#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Player {
public:
    Player(const sf::Vector2f& startPosition);

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

    void loadTexture(const std::string& textureFile);
};

#endif // PLAYER_HPP
