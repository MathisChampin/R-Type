#pragma once

#include <cstdint>

namespace NmpServer
{
    enum class EVENT : uint32_t {
        MOVE = 1,
        SHOOT = 2,
        QUIT = 3,
        SPRITE = 4,
        JOIN = 5,
        EOI = 6,
        LIFE = 7,
        SCORE = 8,
    };

    enum class DIRECTION : uint32_t {
        LEFT = 1,
        RIGHT = 2,
        UP = 3,
        DOWN = 4,
        SHOOT = 5
    };

    struct SpriteInfo {
        int idClient;
        int id;
        int x;
        int y;
        int sizeX;
        int sizeY;
    };
}

