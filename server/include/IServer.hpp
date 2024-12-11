#pragma once

#include "Packet.hpp"
#include <asio.hpp>
#include <iostream>
#include <vector>


namespace NmpServer {
    class IServer {
        public:
            virtual void run() = 0;
            virtual void send_data(Packet &packet, const asio::ip::udp::endpoint &client_endpoint) = 0;
            virtual void get_data() = 0;
            virtual void broadcast(Packet &packet) = 0;
            virtual ~IServer() = default;
    };
}