#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

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

    void run();

private:
    // Initialization methods
    void initializeWindow();
    void initializeFont();
    void initializeMenuOptions();
    void initializeIpAddressText();

    // Network methods
    void get_player();
    void get_ennemies();
    void get_shoots();

    // Event handling
    void handleEvents();
    void processInput(sf::Event& event);

    // Game loop methods
    void update(float deltaTime);
    void render();

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

    // Entity containers
    std::vector<std::unique_ptr<Player>> m_players;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    std::vector<std::unique_ptr<Shoot>> m_shoots;

    // UI elements
    sf::String m_ipAddress;
    sf::Text m_ipText;
    sf::Text m_ipField;

    // Timing
    sf::Clock m_clock;
};

#endif // GAME_HPP