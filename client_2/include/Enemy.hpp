#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy {
public:
    Enemy() = default;

    Enemy(std::string filename, float x, float y, int frameWidth, int frameHeight, int frameCount, float animationSpeed)
        : _frameWidth(frameWidth), _frameHeight(frameHeight), _frameCount(frameCount), _animationSpeed(animationSpeed) {
        if (!_texture.loadFromFile(filename)) {
            std::cerr << "Error loading texture from file: " << filename << std::endl;
        }
        _sprite.setTexture(_texture);
        _sprite.setPosition(sf::Vector2f(x, y));
        _sprite.setTextureRect(sf::IntRect(0, 0, _frameWidth, _frameHeight));
        _currentFrame = 0;
        _elapsedTime = 0.0f;
    }

    ~Enemy() = default;

    void update(float deltaTime) {
        _elapsedTime += deltaTime;

        if (_elapsedTime >= _animationSpeed) {
            _elapsedTime = 0.0f;
            _currentFrame = (_currentFrame + 1) % _frameCount;

            int left = _currentFrame * _frameWidth;
            _sprite.setTextureRect(sf::IntRect(left, 0, _frameWidth, _frameHeight));
        }
    }

    void setPosition(const sf::Vector2f& position) {
        _sprite.setPosition(position);
    }

    void drawSprite(sf::RenderWindow &window)
    {
        window.draw(_sprite);
    }

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    int _frameWidth;
    int _frameHeight;
    int _frameCount;
    float _animationSpeed;
    int _currentFrame;
    float _elapsedTime;
    int score;
    int life;
};
