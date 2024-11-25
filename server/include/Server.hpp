#pragma once

#include "IServer.hpp"
#include <asio.hpp>

namespace NmpServer {
    class Server : public IServer {
        public:
            Server();

            void run() override;
            void send_data(const std::string& message) override;
            void get_data() override;

            void handle_get_data(const std::error_code& error, std::size_t bytes);
            void handle_send_data(const std::error_code& error, std::size_t bytes);

        private:
            asio::io_context _io_context;
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _remote_endpoint;
        std::array<char, 1024> _recv_buffer;
    };
}