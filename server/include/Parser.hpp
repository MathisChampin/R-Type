#pragma once

#include <iostream>
#include <fstream>
#include <vector>

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
            Parser(std::string fileLevel) : _fd(fileLevel) {
                if (_fd.is_open())
                    std::cout << "config file open\n";
                else
                    std::cout << "error while openning file\n";
            };
            ~Parser() {_fd.close();};

            void parseConfig();
            
        private:
            void parseEnnemies(std::string &buffer);
            void displayVec();

            std::ifstream _fd;
            std::vector<infoEnnemies_t> _vecEnnemies;
    };
}