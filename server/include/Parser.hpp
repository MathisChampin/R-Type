#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

namespace NmpServer
{
    typedef struct infoEnnemies_s {
        unsigned int type;
        unsigned int posX;
        unsigned int posY;
        unsigned int delaySpawn;
    } infoEnnemies_t;

    class Parser {
        public:
            Parser(std::string fileLevel) : _fileName(fileLevel) {};
            ~Parser() = default;

            void parseConfig();

            void displayVec();

        private:

            std::string _fileName;
            std::vector<infoEnnemies_t> _vecEnnemies;
    };
}
