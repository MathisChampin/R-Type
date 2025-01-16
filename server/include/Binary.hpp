#pragma once

#include "Packet.hpp"
#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

namespace NmpBinary {
    class SBinary {
        public:
            SBinary() = default;
            ~SBinary() = default;

            void serialize(NmpServer::Packet &packet,  std::vector<int> &buffer);
            NmpServer::Packet deserialize(std::vector<int> &buffer);
            void clearBuffer(std::vector<int> &buffer);
            void printBuffer(std::vector<int> &buffer);

        private:
            std::vector<std::string> getAction(std::string &action);
    };
}