#include "../include/Life.hpp"
#include <iostream>

Life::Life() : m_currentLife(0), m_maxLife(0) {}

Life::~Life() {}

void Life::initialize(const std::string &texturePath, int maxLife, float spacing) {
    m_maxLife = maxLife;

    if (!m_heartTexture.loadFromFile(texturePath)) {
        std::cerr << "Error: Unable to load heart texture!" << std::endl;
        throw std::runtime_error("Failed to load heart texture");
    }

    m_hearts.clear();
    for (int i = 0; i < m_maxLife; ++i) {
        sf::Sprite heart(m_heartTexture);
        heart.setScale(0.1f, 0.1f);
        heart.setPosition(i * (m_heartTexture.getSize().x * 0.1f + spacing), 0.f);
        m_hearts.emplace_back(heart, false);
    }
}

int Life::getNbLife() const {
    int activeHearts = 0;
    for (const auto &elem : m_hearts) {
        if (elem.second) {
            ++activeHearts;
        }
    }
    return activeHearts;
}

void Life::updateLife(int newLife) {
    if (newLife < 0 || newLife > m_maxLife) {
        std::cerr << "Error: Invalid life count!" << std::endl;
        return;
    }

    m_currentLife = newLife;
    for (int i = 0; i < m_maxLife; ++i) {
        m_hearts[i].second = (i < m_currentLife);
    }
}

void Life::render(sf::RenderWindow &window) {
    for (const auto &heart : m_hearts) {
        if (heart.second) {
            window.draw(heart.first);
        }
    }
}
