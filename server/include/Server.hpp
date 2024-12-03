#pragma once

#include "IServer.hpp"
#include "Binary.hpp"
#include <asio.hpp>

namespace NmpServer {
    class Server : public IServer {
        public:
            Server();

            void run() override;
            void send_data(Packet &packet) override;
            void get_data() override;

            void handle_get_data(const std::error_code &error, std::size_t bytes);
            void handle_send_data(const std::error_code &error, std::size_t bytes);

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _remote_endpoint;
            std::vector<uint32_t> _bufferSerialize;
            std::array<uint32_t, 256> _bufferAsio;
            NmpBinary::Binary _binary;
    };
}