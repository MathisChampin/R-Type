#ifndef OPTIONS_MENU_HPP
    #define OPTIONS_MENU_HPP

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>

class OptionsMenu {
    public:
        OptionsMenu(sf::RenderWindow& window);

        void handleEvent(const sf::Event& event);
        void update();
        void render();

    private:
        sf::RenderWindow& m_window;
        sf::Font m_font;
        sf::Text m_titleText;
        sf::Text m_volumeText;
        sf::RectangleShape m_volumeBarBackground;
        sf::RectangleShape m_volumeBarForeground;
        float m_volume;
        sf::Music m_music;

        void setupTitleText();
        void setupVolumeText();
        void setupVolumeBar();
        void updateVolumeBar();
        void updateMusicVolume();
};

#endif // OPTIONS_MENU_HPP