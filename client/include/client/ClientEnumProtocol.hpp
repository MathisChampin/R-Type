#pragma once

#include <cstdint>

namespace NmpClient
{
    enum class EVENT : int
    {
        MOVE = 1,
        SHOOT = 2,
        QUIT = 3,
        SPRITE = 4,
        JOIN = 5,
        EOI = 6,
        INFO = 7
    };

    enum class DIRECTION : int
    {
        LEFT = 1,
        RIGHT = 2,
        UP = 3,
        DOWN = 4,
        SHOOT = 5
    };

    struct SpriteInfo
    {
        int idClient;
        int id;
        int x;
        int y;
        int sizeX;
        int sizeY;
    };
}
