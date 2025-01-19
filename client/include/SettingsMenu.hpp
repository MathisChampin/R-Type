#ifndef SETTINGSMENU_HPP
#define SETTINGSMENU_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"

class SettingsMenu
{
public:
    SettingsMenu(sf::RenderWindow &window, SoundManager &soundManager);
    void handleEvent(const sf::Event &event);
    void update();
    void render();





private:
    sf::RenderWindow &m_window;
    sf::Font m_font;
    SoundManager &m_soundManager;

    // Textes
    sf::Text m_titleText;
    sf::Text m_volumeText;
    sf::Text m_fpsText;

    // Barres
    sf::RectangleShape m_volumeBarBackground;
    sf::RectangleShape m_volumeBarForeground;
    sf::RectangleShape m_fpsBarBackground;
    sf::RectangleShape m_fpsBarForeground;

    // Variables
    float m_volume;
    int m_fps;

    // Méthodes
    void setupTitleText();
    void setupVolumeText();
    void setupVolumeBar();
    void setupFPSText();
    void setupFPSBar();
    void updateVolumeBar();
    void updateFPSBar();
};

#endif // SETTINGS_MENU_HPP
