#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Menu.hpp"
#include "ParallaxBackground.hpp"
#include "Player.hpp"
#include "OptionsMenu.hpp"
#include "client/Client.hpp"
#include "Enemy.hpp"
#include "Shoot.hpp"
#include "client/TextureManager.hpp"
#include "client/Sprite.hpp" 

enum class GameState {
    Menu,
    Playing,
    Options,
    PlayingInLobby
};

class Game {
public:
    Game();
    ~Game();

    void boucle();
    void run();

private:
    // Window and rendering
    void initializeWindow();
    void initializeFont();
    void initializeMenuOptions();
    void initializeIpAddressText();
    void get_join_packet();
    // Event handling
    void handleEvents();
    void processInput(sf::Event& event);
    // Game loop methods
    void update(float deltaTime);
    void render();
    void get_player();
    void get_ennemies();
    void get_shoots();
    // Member variables
    sf::RenderWindow m_window;
    sf::Font m_font;
    GameState m_currentState;

    // Game components
    Menu m_menu;
    OptionsMenu m_optionsMenu;
    ParallaxBackground m_menuBackground;
    ParallaxBackground m_playingBackground;
    NmpClient::Client m_client;
    TextureManager& textureManager = TextureManager::getInstance();

    // Vectors to store players and enemies
    std::vector<Player> m_players;
    std::vector<Enemy> m_enemies;
    std::vector<Shoot> m_shoots;

    // IP address input
    sf::String m_ipAddress;
    sf::Text m_ipText;
    sf::Text m_ipField;

    // Clock for delta time calculation
    sf::Clock m_clock;
};

#endif // GAME_HPP
