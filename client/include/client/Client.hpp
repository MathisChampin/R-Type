#pragma once

#include "IClient.hpp"
#include <iostream>
#include <asio.hpp>

namespace NmpClient {
    class Client : public IClient {
        public:
            Client();

            void send_input() override;
            void get_data() override;

        private:
            asio::io_context _io_context;
            asio::ip::udp::resolver _resolver;
            asio::ip::udp::endpoint _receiver_endpoint;
            asio::ip::udp::socket _socket;
            std::array<char, 1024> buffer;
    };
}