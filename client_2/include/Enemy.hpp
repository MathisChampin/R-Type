#pragma once
#include <SFML/Graphics.hpp>

class Enemy : public sf::Sprite {
    public:
        Enemy();
        void update();
    private:
        sf::Texture texture;
        float speed;
};

