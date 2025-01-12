#ifndef LIFE_HPP
#define LIFE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Life {
public:
    Life();
    ~Life();

    void initialize(const std::string &texturePath);
    void updateLife(int newLife);
    void render(sf::RenderWindow &window);

private:
    sf::Texture m_heartTexture;
    std::vector<sf::Sprite> m_hearts;
    int m_currentLife;
};

#endif // LIFE_HPP
