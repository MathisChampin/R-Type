#include "Parser.hpp"

namespace NmpServer
{
    void Parser::parseConfig()
    {
        _vecEnnemies.clear();

        std::ifstream file(_fileName);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << _fileName << std::endl;
            return;
        }

        nlohmann::json jsonConfig;
        file >> jsonConfig;
        file.close();

        try {
            for (const auto &enemy : jsonConfig) {
                infoEnnemies_t structEnnemies;

                structEnnemies.type = enemy.at("type").get<unsigned int>();
                structEnnemies.posX = enemy.at("posX").get<unsigned int>();
                structEnnemies.posY = enemy.at("posY").get<unsigned int>();
                structEnnemies.delaySpawn = enemy.at("delaySpawn").get<unsigned int>();

                _vecEnnemies.push_back(structEnnemies);
            }
        } catch (const nlohmann::json::exception &e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        }

        this->displayVec();
    }

    void Parser::forEachEnnemy(const std::function<void(int, int, int)> &createEnnemies)
    {
        for (const auto &ennemy : _vecEnnemies) {
            createEnnemies(ennemy.type, ennemy.posX, ennemy.posY);
        }
    }

    void Parser::displayVec()
    {
        for (const auto &ennemy : _vecEnnemies) {
            std::cout << "type: " << ennemy.type
                      << " posX: " << ennemy.posX
                      << " posY: " << ennemy.posY
                      << " delaySpawn: " << ennemy.delaySpawn << std::endl;
        }
    }
}
