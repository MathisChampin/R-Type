#pragma once

#include "IServer.hpp"
#include "Binary.hpp"
#include "ProtocolHandler.hpp"
#include <mutex>
#include <queue>
#include <thread>
#include <chrono>
#include <map>

namespace NmpServer {
    class Server : public IServer {
        public:
            Server();

            void run() override;
            void get_data() override;
            void send_data(Packet &packet) override;
            void extract_bytes(std::size_t &bytes) override;

            void handle_get_data(const std::error_code &error, std::size_t bytes);
            void handle_send_data(const std::error_code &error, std::size_t bytes);
            void add_to_queue(Packet &packet);

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socketRead;
            asio::ip::udp::socket _socketSend;
            asio::ip::udp::endpoint _remote_endpoint;

            std::vector<uint32_t> _bufferSerialize;
            std::array<uint32_t, 256> _bufferAsio;
            std::queue<Packet> _queueInput;

            NmpBinary::Binary _binary;
            //ProtocoleHandler _ptp;

    };
}