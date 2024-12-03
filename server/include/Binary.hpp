#pragma once

#include "Packet.hpp"
#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

namespace NmpBinary {
    class Binary {
        public:
            Binary() = default;
            ~Binary() = default;

            void serialize(NmpServer::Packet &packet,  std::vector<uint32_t> &buffer);
            NmpServer::Packet deserialize(std::vector<uint32_t> &buffer);
            void clearBuffer(std::vector<uint32_t> &buffer);
            void printBuffer(std::vector<uint32_t> &buffer);

        private:
            std::vector<std::string> getAction(std::string &action);
            uint8_t getOctets(uint32_t &code, unsigned int octets);
    };
}