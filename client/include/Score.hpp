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
    sf::Text m_scoreText;  // Texte affichant le score
    int m_currentScore;    // Valeur actuelle du score
};

#endif // SCORE_HPP
