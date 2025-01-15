#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <map>
#include <unordered_set>
#include <optional>

//#include "Engine.hpp"
#include "SoundManager.hpp"
#include "State.hpp"
#include "ParallaxBackground.hpp"
#include "CustomMenu.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Shoot.hpp"
#include "SpriteManager.hpp"
#include "Life.hpp"
#include "Score.hpp"
#include "Type.hpp"
#include "client/Client.hpp"

class Game
{
public:
    //Game() = default;
    Game(sf::RenderWindow &window, SkinType skinType, sf::Font &font, ParallaxBackground &playingBackground, SoundManager &soundManager);
    ~Game();

    void run();
    void handleEvents();
    void update(float deltaTime);
    void render(float deltaTime);
    void handler_packets();

private:
    // Initialization

    // Network methods
    void get_player();
    void get_ennemies();
    void get_shoots();

    // Event handling
    void processInput(sf::Event &event);

    // Game loop methods

    void get_player(NmpClient::SpriteInfo &sp);
    void get_ennemies(NmpClient::SpriteInfo &sp);
    void get_ennemies2(NmpClient::SpriteInfo &sp);
    void get_ennemies3(NmpClient::SpriteInfo &sp);
    void get_ennemies4(NmpClient::SpriteInfo &sp);
    void get_ennemies5(NmpClient::SpriteInfo &sp);
    void get_shoots(NmpClient::SpriteInfo &sp);

    void launch_getter(std::size_t id, NmpClient::SpriteInfo &sp);
    void destroy_useless_sprites();

    // Game state
    SkinType m_skinType;    

    // Window (reference)
    sf::RenderWindow &m_window;

    // Parallax background
    ParallaxBackground m_playingBackground;

    // Game components
    NmpClient::Client m_client;
    Player m_players;

    // Vectors to store players and enemies
    std::vector<Enemy> m_enemies;
    std::vector<Shoot> m_shoots;

    // Timing
    sf::Clock m_clock;

    // Current state
    GameState m_currentState;

    // Font (reference)
    sf::Font &m_font;

    // Sound
    SoundManager m_SoundManager;  

    SpriteManager _spriteMng;
    std::unordered_set<std::size_t> _containerEndFrameId;
    std::queue<NmpClient::Packet> _queuePacket;
    std::map<std::size_t, std::function<void(NmpClient::SpriteInfo &sp)>> _mapHandlerPacket{
        {1, [this](NmpClient::SpriteInfo &sp)
         { get_player(sp); }},
        {2, [this](NmpClient::SpriteInfo &sp)
         { get_shoots(sp); }},
        {3, [this](NmpClient::SpriteInfo &sp)
         { get_ennemies(sp); }},
        {4, [this](NmpClient::SpriteInfo &sp)
         { get_ennemies2(sp); }},
        {5, [this](NmpClient::SpriteInfo &sp)
         { get_ennemies3(sp); }},
        {6, [this](NmpClient::SpriteInfo &sp)
         { get_ennemies4(sp); }},
        {7, [this](NmpClient::SpriteInfo &sp)
         { get_ennemies5(sp); }},
        {8, [this](NmpClient::SpriteInfo &sp)
         { get_shoots(sp); }},
        {9, [this](NmpClient::SpriteInfo &sp)
         { get_shoots(sp); }},
        {10, [this](NmpClient::SpriteInfo &sp)
         { get_shoots(sp); }},
    };

    Life m_life;
    Score m_score;
};

#endif // GAME_HPP
