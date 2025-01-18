#ifndef DEATHANIMATION_HPP
#define DEATHANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class DeathAnimation {
public:
    DeathAnimation();
    ~DeathAnimation();

    void initialize(const std::string &basePath, int frameCount, int maxAnimations, float spacing = 10.f, float duration = 1.0f);
    void triggerAnimation(int index);
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    bool isAnimationActive(int index) const;
    void setAnimationPosition(sf::Vector2f position);

private:
    std::vector<sf::Texture> m_textures;
    std::vector<std::pair<sf::Sprite, float>> m_animations;
    int m_frameCount;
    int m_maxAnimations;
    float m_animationDuration;
    float m_frameTime;
};

#endif // DEATHANIMATION_HPP
