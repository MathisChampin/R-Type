#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Shoot {
public:
    Shoot() = default;

    Shoot(size_t id, std::string filename, float x, float y)
        : _id{id} {
        if (!_texture.loadFromFile(filename)) {
            std::cerr << "Error loading texture from file: " << filename << std::endl;
        }
        _sprite.setTexture(_texture);
        _sprite.setPosition(sf::Vector2f(x, y));
    }

    ~Shoot() = default;

    void setPosition(const sf::Vector2f& position) {
        _sprite.setPosition(position);
    }

    void drawSprite(sf::RenderWindow &window)
    {
        window.draw(_sprite);
    }

    size_t get_id() {
        return _id;
    }
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    size_t _id;
};
