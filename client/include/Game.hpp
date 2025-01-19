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
#include "Level.hpp"

class Game
{
public:
    //Game() = default;
    Game(std::string ip, sf::RenderWindow &window, SkinType skinType, sf::Font &font, ParallaxBackground &playingBackground, SoundManager &soundManager);
    ~Game();

    void run();
    void handleEvents();
    void update(float deltaTime);
    void render(float deltaTime);
    bool AnimationLevel();
    bool AnimationLevelGame();

    int getLevel() const {
        return m_level.getLevel();
    }
    int getLevelGame() const {
        return m_level_game;
    }

    bool getDead() const {
        return m_dead;
    }
    void handler_packets();
    Score m_score;

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

    void get_shoots2(NmpClient::SpriteInfo &sp);
    void get_shoots3(NmpClient::SpriteInfo &sp);
    void get_shoots4(NmpClient::SpriteInfo &sp);
    void get_shoots5(NmpClient::SpriteInfo &sp);
    void get_powerup_life(NmpClient::SpriteInfo &sp);
    void get_powerup_move(NmpClient::SpriteInfo &sp);
    void get_shoots6(NmpClient::SpriteInfo &sp);
    void get_shoots7(NmpClient::SpriteInfo &sp);
    void get_shoots8(NmpClient::SpriteInfo &sp);
    void get_shoots9(NmpClient::SpriteInfo &sp);
    void get_shoots10(NmpClient::SpriteInfo &sp);
    void get_shoots11(NmpClient::SpriteInfo &sp);
    // void handler_packets();

    void launch_getter(std::size_t id, NmpClient::SpriteInfo &sp);
    void destroy_useless_sprites();

    std::string _ip;
    // Game state
    sf::RenderWindow &m_window;
    SkinType m_skinType;    

    // Window (reference)

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
        {1, [this](NmpClient::SpriteInfo &sp) { get_player(sp); }},
        {2, [this](NmpClient::SpriteInfo &sp) { get_ennemies(sp); }},
        {3, [this](NmpClient::SpriteInfo &sp) { get_ennemies2(sp); }},
        {4, [this](NmpClient::SpriteInfo &sp) { get_ennemies3(sp); }},
        {5, [this](NmpClient::SpriteInfo &sp) { get_ennemies4(sp); }},
        {6, [this](NmpClient::SpriteInfo &sp) { get_ennemies5(sp); }},
        {7, [this](NmpClient::SpriteInfo &sp) { get_shoots(sp); }},
        {8, [this](NmpClient::SpriteInfo &sp) { get_shoots2(sp); }},
        {9, [this](NmpClient::SpriteInfo &sp) { get_shoots3(sp); }},
        {10, [this](NmpClient::SpriteInfo &sp) { get_shoots4(sp); }},
        {11, [this](NmpClient::SpriteInfo &sp) { get_powerup_life(sp); }},
        {12, [this](NmpClient::SpriteInfo &sp) { get_powerup_move(sp); }},
        {13, [this](NmpClient::SpriteInfo &sp) { get_shoots5(sp); }},
        {14, [this](NmpClient::SpriteInfo &sp) { get_shoots6(sp); }},
        {15, [this](NmpClient::SpriteInfo &sp) { get_shoots7(sp); }},
        {16, [this](NmpClient::SpriteInfo &sp) { get_shoots8(sp); }},
        {17, [this](NmpClient::SpriteInfo &sp) { get_shoots9(sp); }},
        {18, [this](NmpClient::SpriteInfo &sp) { get_shoots10(sp); }},
        {19, [this](NmpClient::SpriteInfo &sp) { get_shoots11(sp); }},
    };

    Life m_life;
    Level m_level;
    int m_level_game{0};
    int m_level_previous_game{0};
    int m_previousLevel;
    bool m_dead{false};
};

#endif // GAME_HPP
