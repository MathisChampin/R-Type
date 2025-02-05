#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
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
            void loadNewLevel(std::string file);
            std::vector<infoEnnemies_t> getVector() const;


        private:
            void displayVec();

            std::string _fileName;
            std::vector<infoEnnemies_t> _vecEnnemies;
    };
}
