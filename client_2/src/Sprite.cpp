#include "../include/Sprite.hpp"
#include <iostream>

Sprite::Sprite(std::string filename, float x, float y)
{
    if (!_texture.loadFromFile(filename)) {
        std::cerr << "Error loading texture from file: " << filename << std::endl;
    }
    _sprite.setTexture(_texture);
    _sprite.setPosition(sf::Vector2f(x, y));
    float scaleX = 1920.0f / _texture.getSize().x;
    float scaley = 1080.0f / _texture.getSize().y;
    _sprite.setScale(scaleX, scaley);
}

void Sprite::drawSprite(sf::RenderWindow &w)
{
    w.draw(_sprite);
}

Sprite& Sprite::operator=(const Sprite &obj)
{
    if (this != &obj) {
        _texture = obj._texture;
        _sprite = obj._sprite;
        _sprite.setTexture(_texture);
    }
    return *this;
}

void Sprite::moveRect(int offset, int maxValue)
{
    if (_rec.left != maxValue) {
        _rec.left += offset;
    } else {
        _rec.left = 0;
    }
    _sprite.setTextureRect(_rec);
}

void Sprite::initRect()
{
    _rec.top = 0;
    _rec.left = 0;
    _rec.width = 1920;
    _rec.height = 1080;
}
