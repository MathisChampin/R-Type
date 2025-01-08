#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Menu.hpp"
#include "ParallaxBackground.hpp"
#include "Player.hpp"
#include "OptionsMenu.hpp"
#include "client/Client.hpp"
#include "Enemy.hpp"
#include "Shoot.hpp"
#include "SpriteManager.hpp"
// #include "client/TextureManager.hpp"
// #include "client/Sprite.hpp"

enum class GameState
{
    Menu,
    Playing,
    Options,
    PlayingInLobby
};

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    // Initialization
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
    void processInput(sf::Event &event);

    // Game loop methods
    void update(float deltaTime);
    void render(float deltaTime);


    void get_player(NmpClient::SpriteInfo &sp);
    void get_ennemies(NmpClient::SpriteInfo &sp);
    void get_shoots(NmpClient::SpriteInfo &sp);
    void handler_packets();
    void launch_getter(std::size_t id, NmpClient::SpriteInfo &sp);
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

    // Vectors to store players and enemies
    Player m_players;
    std::vector<Enemy> m_enemies;
    std::vector<Shoot> m_shoots;

    // UI elements
    sf::String m_ipAddress;
    sf::Text m_ipText;
    sf::Text m_ipField;

    // Timing
    sf::Clock m_clock;

    SpriteManager _spriteMng;
    std::map<std::size_t, std::function<void(NmpClient::SpriteInfo &sp)>> _mapHandlerPacket{
        {1, [this](NmpClient::SpriteInfo &sp) { get_player(sp); }},
        {2, [this](NmpClient::SpriteInfo &sp) { get_ennemies(sp); }},
        {3, [this](NmpClient::SpriteInfo &sp) { get_shoots(sp); }},
    };

};

#endif // GAME_HPP