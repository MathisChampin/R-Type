#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace NmpServer
{
    class ProceduralLevel {
        public:
            ProceduralLevel(){srand((unsigned) time(NULL));};
            ~ProceduralLevel() = default;

            int createRandValue(const int lim, const int range, const bool zero);
            void generateLevel(int nbEnnemies);

        private:
            int _posX;
            int _posY;
            int _type;
    };
}