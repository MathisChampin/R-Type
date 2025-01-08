#pragma once
#include <SFML/Graphics.hpp>
#include "./Background.hpp"
#include "./Ecs.hpp"
#include "./Player.hpp"
#include "./Text.hpp"
#include "./Enemy.hpp"
#include <memory>

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
        std::vector<std::shared_ptr<Enemy>> enemies;
        float enemySpawnTimer = 0.0f;
        void handleInput();
        void update(float);
        void render();
};
