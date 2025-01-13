#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <functional>

class Menu
{
public:
    /// @brief Constructor for the Menu class.
    /// @param window Reference to an SFML window used to display the menu.
    Menu(sf::RenderWindow &window);

    /// @brief Adds an option to the menu.
    /// @param text The text displayed for this option.
    /// @param callback Function called when the user selects this option.
    void addOption(const std::string &text, std::function<void()> callback);

    /// @brief Handles events for the menu.
    /// @param event The event to be handled.
    void handleEvent(const sf::Event &event);

    void update();
    void render();

private:
    bool loadFont();
    bool loadMusic();
    void setupMusic();
    void setupTitle();
    void setupFooter();
    void setupCredits();
    bool isMouseOverOption(const sf::Text &option, float mouseX, float mouseY) const;
    void updateHoveredItem(float mouseX, float mouseY);

    sf::RenderWindow &m_window;
    sf::Font m_font;
    std::vector<sf::Text> m_options;
    std::vector<std::function<void()>> m_callbacks;
    int m_hoveredItem;
    // sf::Music m_music;

    sf::Text m_title;
    sf::Text m_footer;
    std::vector<sf::Text> m_credits;
};

#endif // MENU_HPP
