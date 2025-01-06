#include "../include/Enemy.hpp"
#include <iostream>

Enemy::Enemy() {
    if (!texture.loadFromFile("assets/ennemi.png")) {
        std::cerr << "Texture not found" << std::endl;
    }
    setTexture(texture);
    speed = 2;
    setPosition(800, rand() % 400);
}

void Enemy::update() {
    move(-speed, 0);
    if (getPosition().x < 0) {
        setPosition(800, rand() % 400);
    }
}
