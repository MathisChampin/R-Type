#include "../include/Life.hpp"
#include <iostream>

Life::Life() : m_currentLife(0) {}

Life::~Life() {}

void Life::initialize(const std::string &texturePath) {
    if (!m_heartTexture.loadFromFile(texturePath)) {
        std::cerr << "Error: Unable to load heart texture!" << std::endl;
        throw std::runtime_error("Failed to load heart texture");
    }
}

void Life::updateLife(int newLife) {
    m_currentLife = newLife;
    m_hearts.clear();
    for (int i = 0; i < m_currentLife; ++i) {
        sf::Sprite heart(m_heartTexture);
        heart.setScale(0.1f, 0.1f);
        heart.setPosition(20 + i * 30, 20);
        m_hearts.push_back(heart);
    }
}

void Life::render(sf::RenderWindow &window) {
    for (const auto &heart : m_hearts) {
        window.draw(heart);
    }
}
