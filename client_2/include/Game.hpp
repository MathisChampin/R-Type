#pragma once
#include <SFML/Graphics.hpp>
#include "./Background.hpp"
#include "./Ecs.hpp"
#include "./Player.hpp"
#include "./Text.hpp"
#include "./Enemy.hpp"

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    LOSE,
    WIN
};

class Game {
    public:
        Game(registry);
        void run();

    private:
        sf::RenderWindow window;
        GameECS _ecs;
        Background background;
        Player player;
        TextManager text;
        float enemySpawnTimer = 0.0f;
        void handleInput();
        void handleMenuInput();
        void update(float);
        void render();
        void renderMenu();
        void renderGameWin();
        void renderGameOver();

        sf::Texture playButtonTexture;
        sf::Texture exitButtonTexture;
        sf::Sprite playButtonSprite;
        sf::Sprite exitButtonSprite;

        sf::Font titleFont;
        sf::Text titleText;
        sf::Font endGameFont;
        int state = 0;
        GameState gameState = GameState::MENU;
};
