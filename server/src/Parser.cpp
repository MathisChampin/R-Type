#include "Parser.hpp"
#include <sstream>

namespace NmpServer
{
    void Parser::parseConfig()
    {
        std::string buffer;
        std::stringstream sstream;

        std::cout << "parse config\n";
        while (std::getline(_fd, buffer))
            this->parseEnnemies(buffer);
        this->displayVec();
    }

    void Parser::parseEnnemies(std::string &buffer)
    {
        std::stringstream sstream(buffer);
        infoEnnemies_t structEnnemies;

        sstream >> 
        structEnnemies.type >>
        structEnnemies.posX >>
        structEnnemies.posY >>
        structEnnemies.delaySpawn;

        _vecEnnemies.push_back(structEnnemies);
    }

    void Parser::displayVec()
    {
        for (auto ennemies : _vecEnnemies) {
            std::cout << "type: " << ennemies.type << " posX: " << ennemies.posX <<
            " posY: " << ennemies.posY << " delay: " << ennemies.delaySpawn << std::endl;
        }
    }
}