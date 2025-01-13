#ifndef LIFE_HPP
#define LIFE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Life {
public:
    Life();
    ~Life();

    void initialize(const std::string &texturePath, int maxLife, float spacing = 10.f);
    void updateLife(int newLife);
    void render(sf::RenderWindow &window);
    int getNbLife() const;

private:
    sf::Texture m_heartTexture;
    std::vector<std::pair<sf::Sprite, bool>> m_hearts;
    int m_currentLife;
    int m_maxLife;
};

#endif // LIFE_HPP
