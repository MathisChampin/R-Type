#pragma once

#include "ClientPacket.hpp"
#include <iostream>
#include <optional>

namespace NmpClient 
{
    class IClient {
        public:
            virtual void send_input(Packet &packet) = 0;
            virtual std::optional<Packet> get_data() = 0;
            virtual ~IClient() = default;
    };
}