#include "ProceduralLevel.hpp"

namespace NmpServer
{
    int ProceduralLevel::createRandValue(const int lim, const int range, const bool zero)
    {
        if (!zero)
            return rand() % lim;
        return range + (rand() % lim);
    }

    void ProceduralLevel::generateGroup(nlohmann::json& level, int groupSize, int centerX, int centerY, int dispersion, int type, int delaySpawn)
    {
        for (int i = 0; i < groupSize; ++i) {
            int posX = centerX + createRandValue(dispersion, -dispersion / 2, true);
            int posY = centerY + createRandValue(dispersion, -dispersion / 2, true);
    
            level.push_back({
                {"type", type},
                {"posX", posX},
                {"posY", posY},
                {"delaySpawn", delaySpawn}
            });
        }
    }


void ProceduralLevel::generateLevel(int nbGroups, Difficulty difficulty)
{
    nlohmann::json level = nlohmann::json::array();

    int groupSizeMin = 2;
    int groupSizeMax = 5;
    int dispersion = 50;
    int spawnDelayRange = 10;

    switch (difficulty) {
        case Difficulty::Easy:
            groupSizeMin = 2;
            groupSizeMax = 4;
            dispersion = 300;
            spawnDelayRange = 15;
            break;
        case Difficulty::Medium:
            groupSizeMin = 3;
            groupSizeMax = 6;
            dispersion = 200;
            spawnDelayRange = 10;
            break;
        case Difficulty::Hard:
            groupSizeMin = 5;
            groupSizeMax = 8;
            dispersion = 100;
            spawnDelayRange = 5;
            break;
    }

    for (int i = 0; i < nbGroups; ++i) {
        int groupSize = createRandValue(groupSizeMax - groupSizeMin + 1, groupSizeMin, true);
        int centerX = createRandValue(100, 1700, true);
        int centerY = createRandValue(800, 100, true);
        int type = createRandValue(4, 1, true);
        int delaySpawn = createRandValue(spawnDelayRange, 2, true);

        generateGroup(level, groupSize, centerX, centerY, dispersion, type, delaySpawn);
    }

    std::ofstream file("../../server/configFile/level1.json");
    if (file.is_open()) {
        file << level.dump(4);
        file.close();
        std::cout << "Niveau écrit dans level1.json" << std::endl;
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour écrire le niveau." << std::endl;
    }
}

}

