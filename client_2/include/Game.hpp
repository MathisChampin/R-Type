#pragma once
#include <SFML/Graphics.hpp>
#include "./Player.hpp"
#include "./Enemy.hpp"
#include "./Background.hpp"
#include "./Ecs.hpp"

class Game {
    public:
        Game();
        void run();
    private:
        sf::RenderWindow window;
        Player player;
        GameECS ecs;
        Background background;
        std::vector<Enemy> enemies;

        void handleInput();
        void update(float);
        void render();
};
