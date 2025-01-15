#include "ProceduralLevel.hpp"

namespace NmpServer
{
    int ProceduralLevel::createRandValue(const int lim, const int range, const bool zero)
    {
        if (!zero)
            return rand() % lim;
        return range + (rand() % lim);
    }


    void ProceduralLevel::generateLevel(int nbEnnemies)
    {
        nlohmann::json level = nlohmann::json::array();

        for (int i = 0; i < nbEnnemies; ++i) {
            _type = createRandValue(4, 1, true);
            _posX = createRandValue(900, 100, true);
            _posY = createRandValue(800, 100, true); 
            int delaySpawn = createRandValue(5, 0, true); 

            level.push_back({
                {"type", _type},
                {"posX", _posX},
                {"posY", _posY},
                {"delaySpawn", delaySpawn}
            });
        }

        std::ofstream file("../../server/configFile/level1.json");
        if (file.is_open()) {
            file << level.dump(4);
            file.close();
            std::cout << "json write in test.json" << std::endl;
        } else {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier pour écrire le niveau." << std::endl;
        }
    }
    // }
}

// namespace NmpServer
// {
//     int ProceduralLevel::createRandValue(const int lim, const int range, const bool zero)
//     {
//         if (!zero)
//             return rand() % lim;
//         return range + (rand() % lim);
//     }



// }
