#pragma once
#include <SFML/Graphics.hpp>
#include "./Background.hpp"
#include "./Ecs.hpp"
#include "./Player.hpp"

class Game {
    public:
        Game(registry);
        void run();
    private:
        sf::RenderWindow window;
        GameECS _ecs;
        Background background;
        Player player;
        void handleInput();
        void update(float);
        void render();
};
