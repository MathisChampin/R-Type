#pragma once
#include <SFML/Graphics.hpp>
#include "./Background.hpp"
#include "./Ecs.hpp"
#include "./Player.hpp"
#include "./Text.hpp"
#include "./Enemy.hpp"

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
        void update(float);
        void render();
};
