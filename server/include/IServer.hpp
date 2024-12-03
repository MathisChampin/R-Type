#pragma once

#include "Packet.hpp"
#include <iostream>

namespace NmpServer {
    class IServer {
        public:
            virtual void run() = 0;
            virtual void send_data(Packet &packet) = 0;
            virtual void get_data() = 0;
            virtual ~IServer() = default;
    };
}