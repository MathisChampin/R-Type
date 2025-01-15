#ifndef LEVEL_HPP
    #define LEVEL_HPP

    #include <SFML/Graphics.hpp>

class Level {
public:
    Level();
    ~Level();

    void initialize(const sf::Font &font, unsigned int characterSize, const sf::Vector2f &position);
    void updateLevel(int newLevel);
    bool checkLevel()
    {
        if (m_currentLevel == 3 || m_currentLevel == 4 || m_currentLevel == 5 ||
        m_currentLevel == 6)
            return true;
        return false;
    }
    void render(sf::RenderWindow &window);

private:
    sf::Text m_levelText;
    int m_currentLevel;
};

#endif // SCORE_HPP
