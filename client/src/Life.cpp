#include "../include/Life.hpp"
#include <iostream>

Life::Life() : m_currentLife(0), m_maxLife(0) {}

Life::~Life() {}

void Life::initialize(const std::string &fullTexturePath, const std::string &midTexturePath, const std::string &lowTexturePath, int maxLife) {
    m_maxLife = maxLife;

    if (!m_fullTexture.loadFromFile(fullTexturePath) ||
        !m_midTexture.loadFromFile(midTexturePath) ||
        !m_lowTexture.loadFromFile(lowTexturePath)) {
        std::cerr << "Error: Unable to load life bar textures!" << std::endl;
        throw std::runtime_error("Failed to load life bar textures");
    }

    m_lifeBar.setTexture(m_fullTexture);
    m_lifeBar.setScale(1.5f, 1.5f);
    m_lifeBar.setPosition(0.f, 0.f);
}

int Life::getNbLife() const {
    return m_currentLife;
}

void Life::updateLife(int newLife) {
    if (newLife < 0 || newLife > m_maxLife) {
        std::cerr << "Error: Invalid life count!" << std::endl;
        return;
    }

    m_currentLife = newLife;

    if (m_currentLife > m_maxLife / 2) {
        m_lifeBar.setTexture(m_fullTexture);
    } else if (m_currentLife > m_maxLife / 4) {
        m_lifeBar.setTexture(m_midTexture);
    } else if (m_currentLife > 0) {
        m_lifeBar.setTexture(m_lowTexture);
    }
}

void Life::render(sf::RenderWindow &window) {
    if (m_currentLife > 0) {
        window.draw(m_lifeBar);
    }
}
