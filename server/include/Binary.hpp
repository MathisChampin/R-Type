#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

namespace NmpBinary {
    class Binary {
        public:
            Binary() = default;
            ~Binary() = default;

            void serialize(std::string action,  std::vector<uint32_t> &buffer);
            std::string deserialize(std::vector<uint32_t> &buffer);

        private:
            std::vector<std::string> getAction(std::string &action);
            uint8_t getOctets(uint32_t &code, unsigned int octets);
    };
}