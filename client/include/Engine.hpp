// Engine.hpp
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Menu.hpp"
#include "Game.hpp"
#include "OptionsMenu.hpp"
#include "CustomMenu.hpp"
#include "SettingsMenu.hpp"
// #include "SoundManager.hpp"
#include "ParallaxBackground.hpp"
#include "State.hpp"
#include "Infos.hpp"
//class Game;
class Engine
{
public:
    Engine();
    ~Engine() = default;

    void run();

private:
    void initializeWindow();
    void setupMenuOptions();
    void initializeFont();
    void initializeSoundManager();
    void handleEvents();
    void update(float deltaTime);
    void render(float deltaTime);
    void triggerPopup(const std::string &, const std::string &);
    void renderPopup();
    void renderDeathPopup(int score);

    bool gameCreated{false};
    sf::RenderWindow m_window;
    sf::Font m_font;
    std::unique_ptr<Menu> m_menu;
    std::unique_ptr<OptionsMenu> m_optionsMenu;
    std::unique_ptr<CustomMenu> m_customMenu;
    std::unique_ptr<SettingsMenu> m_settingsMenu;
    SoundManager m_soundManager;
    std::unique_ptr<Game> m_game;
    std::unique_ptr<Infos> m_infoSection;

    std::unique_ptr<ParallaxBackground> m_menuBackground;
    std::unique_ptr<ParallaxBackground> m_levelBackground;
    std::unique_ptr<ParallaxBackground> m_infosBackground;
    std::unique_ptr<ParallaxBackground> m_playingBackground;
    std::unique_ptr<ParallaxBackground> m_customBackground;
    std::unique_ptr<ParallaxBackground> m_settingsBackground;

    GameState m_currentState;
    sf::Clock m_clock;
    std::string m_creatorIp;
    int level;
    float m_animationTime;
    sf::Clock m_popupClock;
    bool m_showPopup;  
    bool m_created{false};                    
    sf::Texture m_popupTexture;            
    sf::Sprite m_popupSprite;          
    std::string m_popupMessage;
};

#endif // ENGINE_HPP
