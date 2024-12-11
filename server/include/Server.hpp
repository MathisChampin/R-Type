#pragma once

#include "IServer.hpp"
#include "Binary.hpp"
#include "ProtocolHandler.hpp"
#include <mutex>
#include <map>

namespace NmpServer {
    class Server : public IServer {
        public:
            Server();

            void run() override;
            void send_data(Packet &packet, const asio::ip::udp::endpoint &client_endpoint) override;
            void get_data() override;
            void broadcast(Packet &packet) override;

            void handle_get_data(const std::error_code &error, std::size_t bytes);
            void handle_send_data(const std::error_code &error, std::size_t bytes);

            asio::ip::udp::endpoint _remote_endpoint;
            std::unordered_map<std::string, asio::ip::udp::endpoint> _clients;
        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;

            std::vector<uint32_t> _bufferSerialize;
            std::array<uint32_t, 256> _bufferAsio;

            NmpBinary::Binary _binary;
            ProtocoleHandler _ptp;

            std::mutex _socket_mutex;
    };
}