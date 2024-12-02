#pragma once

#include "IClient.hpp"
#include "Binary.hpp"
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
            std::vector<uint32_t> _buffer;
            std::array<uint32_t, 1024> _test_buffer;
            NmpBinary::Binary _binary;
    };
}