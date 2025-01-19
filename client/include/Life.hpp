#ifndef LIFE_HPP
#define LIFE_HPP

#include <SFML/Graphics.hpp>

class Life {
public:
    Life();
    ~Life();

    void initialize(const std::string &fullTexturePath, const std::string &midTexturePath, const std::string &lowTexturePath, int maxLife);
    void updateLife(int newLife);
    void render(sf::RenderWindow &window);
    int getNbLife() const;

private:
    sf::Texture m_fullTexture;
    sf::Texture m_midTexture;
    sf::Texture m_lowTexture;
    sf::Sprite m_lifeBar;

    int m_currentLife;
    int m_maxLife;
};

#endif // LIFE_HPP
