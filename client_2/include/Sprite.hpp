#pragma once

    #include <SFML/Graphics.hpp>

class Sprite {
    public:
        Sprite() = default;
        Sprite(std::string filename, float x, float y);
        ~Sprite() = default;
        void drawSprite(sf::RenderWindow &w);
        Sprite& operator=(const Sprite &obj);
        void initRect();
        void moveRect(int offset, int maxValue);
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Vector2f _coord;
        sf::IntRect _rec;
};