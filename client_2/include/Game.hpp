#pragma once
#include <SFML/Graphics.hpp>
#include "./Player.hpp"
#include "./Enemy.hpp"
#include "./Background.hpp"

class Game {
    public:
        Game();
        void run();
    private:
        sf::RenderWindow window;
        Player player;
        Background background;
        std::vector<Enemy> enemies;
    
        void handleInput();
        void update();
        void render();
};
