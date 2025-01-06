#pragma once

#include "ClientPacket.hpp"
#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

namespace NmpBinary
{
    class Binary
    {
    public:
        Binary() = default;
        ~Binary() = default;

        /**
         * @brief Serializes the given packet into the provided buffer.
         *
         * @param packet The packet to be serialized.
         * @param buffer The buffer where the serialized data will be stored.
         */
        void serialize(NmpClient::Packet &packet, std::vector<uint32_t> &buffer);

        /**
         * @brief Deserializes the given buffer into a packet.
         *
         * @param buffer The buffer containing the serialized data.
         * @return NmpClient::Packet The deserialized packet.
         */
        NmpClient::Packet deserialize(std::vector<uint32_t> &buffer);

        /**
         * @brief Clears the given buffer.
         *
         * @param buffer The buffer to be cleared.
         */
        void clearBuffer(std::vector<uint32_t> &buffer);

        /**
         * @brief Prints the contents of the given buffer.
         *
         * @param buffer The buffer to be printed.
         */
        void printBuffer(std::vector<uint32_t> &buffer);

    private:
        std::vector<std::string> getAction(std::string &action);
        uint8_t getOctets(uint32_t &code, unsigned int octets);
    };
}