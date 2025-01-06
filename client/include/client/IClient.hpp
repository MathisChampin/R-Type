#pragma once

#include "ClientPacket.hpp"
#include <iostream>
#include <optional>

namespace NmpClient
{
    class IClient
    {
    public:
        /**
         * @brief Sends input data encapsulated in a Packet object.
         *
         * @param packet The Packet object containing the input data to be sent.
         */
        virtual void send_input(Packet &packet) = 0;
        virtual std::optional<Packet> get_data() = 0;
        virtual ~IClient() = default;
    };
}