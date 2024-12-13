#pragma once

#include "Packet.hpp"
#include <asio.hpp>
#include <iostream>
#include <vector>


namespace NmpServer {
    class IServer {
        public:
            virtual void run() = 0;
            virtual void send_data(Packet &packet) = 0;
            virtual void get_data() = 0;
            virtual void extract_bytes(std::size_t &bytes) = 0;
            virtual ~IServer() = default;
    };
}