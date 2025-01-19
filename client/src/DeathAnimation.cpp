#include "../include/DeathAnimation.hpp"
#include <iostream>
#include <sstream>

DeathAnimation::DeathAnimation()
    : m_frameCount(0), m_maxAnimations(0), m_animationDuration(1.0f), m_frameTime(0.0f) {}

DeathAnimation::~DeathAnimation() {}

void DeathAnimation::initialize(const std::string &basePath, int frameCount, int maxAnimations, float spacing, float duration) {
    m_frameCount = frameCount;
    m_maxAnimations = maxAnimations;
    m_animationDuration = duration;
    m_frameTime = duration / frameCount;

    for (int i = 1; i <= frameCount; ++i) {
        sf::Texture texture;
        std::ostringstream path;
        path << basePath << i << ".png";
        
        if (!texture.loadFromFile(path.str())) {
            std::cerr << "Error: Unable to load texture " << path.str() << std::endl;
            path.str("");
            path << basePath << "/explosions/" << i << ".png";
            
            if (!texture.loadFromFile(path.str())) {
                throw std::runtime_error("Failed to load animation texture: " + path.str());
            }
        }
        m_textures.push_back(std::move(texture));
    }

    m_animations.clear();
    for (int i = 0; i < m_maxAnimations; ++i) {
        sf::Sprite sprite(m_textures[0]);
        sprite.setScale(0.4f, 0.4f);
        sprite.setPosition(i * (m_textures[0].getSize().x * 0.1f + spacing), 0.f);
        m_animations.emplace_back(sprite, 0.f);
    }
}

void DeathAnimation::triggerAnimation(int index) {
    if (index < 0 || index >= m_maxAnimations) {
        std::cerr << "Error: Invalid animation index!" << std::endl;
        return;
    }
    m_animations[index].second = m_animationDuration;
}

void DeathAnimation::setAnimationPosition(sf::Vector2f position) {
    for (auto &animation : m_animations) {
        animation.first.setPosition(position);
    }
}

void DeathAnimation::update(float deltaTime) {
    for (auto &animation : m_animations) {
        if (animation.second > 0.f) {
            animation.second -= deltaTime;
            if (animation.second > 0.f) {
                int frameIndex = static_cast<int>((m_animationDuration - animation.second) / m_frameTime) % m_frameCount;
                animation.first.setTexture(m_textures[frameIndex]);
            } else {
                animation.second = 0.f;
            }
        }
    }
}

void DeathAnimation::render(sf::RenderWindow &window) {
    for (const auto &animation : m_animations) {
        if (animation.second > 0.f) {
            window.draw(animation.first);
        }
    }
}

bool DeathAnimation::isAnimationActive(int index) const {
    if (index < 0 || index >= m_maxAnimations) {
        return false;
    }
    return m_animations[index].second > 0.f;
}