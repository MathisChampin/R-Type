// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <map>

#include "Menu.hpp"
#include "ParallaxBackground.hpp"
#include "Player.hpp"
#include "OptionsMenu.hpp"
#include "client/Client.hpp"
#include "Enemy.hpp"
#include "Shoot.hpp"
#include "SpriteManager.hpp"
#include "Life.hpp"
#include "Score.hpp"
#include "SoundManager.hpp"

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
    // Initialization
    void initializeWindow();
    void initializeFont();
    void initializeMenuOptions();
    void initializeIpAddressText();
    void initializeSoundManager();
    void initializeGameComponents();

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
    void get_ennemies2(NmpClient::SpriteInfo &sp);
    void get_ennemies3(NmpClient::SpriteInfo &sp);
    void get_ennemies4(NmpClient::SpriteInfo &sp);
    void get_ennemies5(NmpClient::SpriteInfo &sp);
    void get_shoots(NmpClient::SpriteInfo &sp);
    void get_shoots2(NmpClient::SpriteInfo &sp);
    void get_shoots3(NmpClient::SpriteInfo &sp);

    void handler_packets();
    void launch_getter(std::size_t id, NmpClient::SpriteInfo &sp);
    void destroy_uselles_sprites();

    // Member variables
    sf::RenderWindow m_window;
    sf::Font m_font;
    GameState m_currentState;

    // Game components
    Menu m_menu;
    OptionsMenu m_optionsMenu;
    ParallaxBackground m_menuBackground;
    ParallaxBackground m_playingBackground;
    std::optional<NmpClient::Client> m_client;
    std::optional<Player> m_players;

    // Vectors to store players and enemies
    std::vector<Enemy> m_enemies;
    std::vector<Shoot> m_shoots;

    // UI elements
    sf::String m_ipAddress;
    sf::Text m_ipText;
    sf::Text m_ipField;

    // Timing
    sf::Clock m_clock;

    // Sound
    SoundManager m_SoundManager;

    SpriteManager _spriteMng;
    std::unordered_set<std::size_t> _containerEndFrameId;
    std::queue<NmpClient::Packet> _queuePacket;
    std::map<std::size_t, std::function<void(NmpClient::SpriteInfo &sp)>> _mapHandlerPacket{
        {1, [this](NmpClient::SpriteInfo &sp) { get_player(sp); }},
        {2, [this](NmpClient::SpriteInfo &sp) { get_ennemies(sp); }},
        {3, [this](NmpClient::SpriteInfo &sp) { get_ennemies2(sp); }},
        {4, [this](NmpClient::SpriteInfo &sp) { get_ennemies3(sp); }},
        {5, [this](NmpClient::SpriteInfo &sp) { get_ennemies4(sp); }},
        {6, [this](NmpClient::SpriteInfo &sp) { get_ennemies5(sp); }},
        {7, [this](NmpClient::SpriteInfo &sp) { get_shoots(sp); }},
        {8, [this](NmpClient::SpriteInfo &sp) { get_shoots2(sp); }},
        {9, [this](NmpClient::SpriteInfo &sp) { get_shoots3(sp); }},
        {10, [this](NmpClient::SpriteInfo &sp) { get_shoots(sp); }},

    };

    Life m_life;
    Score m_score;
};

#endif // GAME_HPP