#ifndef SCORE_HPP
    #define SCORE_HPP

    #include <SFML/Graphics.hpp>

class Score {
public:
    Score();
    ~Score();

    void initialize(const sf::Font &font, unsigned int characterSize, const sf::Vector2f &position);
    void updateScore(int newScore);
    void render(sf::RenderWindow &window);

private:
    void updateBackground();

    sf::Text m_scoreText;
    sf::RectangleShape m_backgroundRect;
    int m_currentScore;
};

#endif // SCORE_HPP
