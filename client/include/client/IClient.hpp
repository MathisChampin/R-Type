#pragma once

#include "ClientPacket.hpp"
#include <iostream>

namespace NmpClient 
{
    class IClient {
        public:
            virtual void send_input(Packet &packet) = 0;
            virtual Packet get_data() = 0;
            virtual ~IClient() = default;
    };
}