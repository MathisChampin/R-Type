#include "../include/Game.hpp"

int main()
{
    registry ecs;

    Game game(ecs);
    game.run();
    return 0;
}