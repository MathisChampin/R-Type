#ifndef ENEMY_HPP
    #define ENEMY_HPP

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <string>

class Enemy
{
    public:
        Enemy(const sf::Vector2f &startPosition);
        void update(float deltaTime);
        void render(sf::RenderWindow &window);

    private:
        sf::Sprite m_sprite;
        std::vector<sf::Texture> m_textures;
        float m_speed;
        int m_currentFrame;
        float m_animationTime;
        float m_elapsedTime;
        int m_direction;
        void loadTexture(const std::string &textureFile);
};

#endif // ENEMY_HPP