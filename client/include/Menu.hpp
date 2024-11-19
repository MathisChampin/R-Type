#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <functional>

class Menu {
public:
    /// @brief Constructeur de la classe Menu.
    /// @param window Référence à une fenêtre SFML utilisée pour afficher le menu.
    Menu(sf::RenderWindow& window);

    /// @brief Ajoute une option au menu.
    /// @param text Le texte affiché pour cette option.
    /// @param callback Fonction appelée lorsque l'utilisateur sélectionne cette option.
    void addOption(const std::string& text, std::function<void()> callback);

    void update();
    void handleEvent(const sf::Event& event);
    void render();

private:
    bool loadFont();

    bool loadMusic();

    void setupMusic();

    void setupTitle();

    void setupFooter();

    void setupCredits();

    bool isMouseOverOption(const sf::Text& option, float mouseX, float mouseY) const;

    void updateHoveredItem(float mouseX, float mouseY);

    sf::RenderWindow& m_window;                
    sf::Font m_font;                          
    std::vector<sf::Text> m_options;          
    std::vector<std::function<void()>> m_callbacks; 
    int m_hoveredItem;                       
    sf::Music m_music;                         

    sf::Text m_title;                          
    sf::Text m_footer;                         
    std::vector<sf::Text> m_credits;         
};

#endif // MENU_HPP
