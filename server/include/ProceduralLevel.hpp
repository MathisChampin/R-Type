#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace NmpServer
{

    enum class Difficulty {
        Easy,
        Medium,
        Hard
    };

    class ProceduralLevel {
        public:
            ProceduralLevel(){srand((unsigned) time(NULL));};
            ~ProceduralLevel() = default;

            int createRandValue(const int lim, const int range, const bool zero);
            void generateGroup(nlohmann::json& level, int groupSize, int centerX, int centerY, int dispersion, int type, int delaySpawn);
            void generateLevel(int nbEnnemies, Difficulty difficulty);

        private:
            int _posX;
            int _posY;
            int _type;
    };
}
