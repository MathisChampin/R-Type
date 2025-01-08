#pragma once
#include <SFML/Graphics.hpp>
#include "./Background.hpp"
#include "./Ecs.hpp"
#include "./Player.hpp"
#include "./Text.hpp"

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
        void handleInput();
        void update(float);
        void render();
};
