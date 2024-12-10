#pragma once

#include <cstdint>

namespace NmpServer
{
    enum class EVENT : uint32_t {
        MOVE = 1,
        SHOOT = 2,
        QUIT = 3,
        SPRITE = 4,
        JOIN = 5
    };

    enum class DIRECTION : uint32_t {
        LEFT = 1,
        RIGHT = 2,
        UP = 3,
        DOWN = 4
    };

    struct SpriteInfo {
        uint32_t id;
        uint32_t x;
        uint32_t y;
        uint32_t sizeX;
        uint32_t sizeY;
    };
}

