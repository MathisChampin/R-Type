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
            void send_data(Packet &packet, asio::ip::udp::endpoint enpoint) override;
            void extract_bytes(std::size_t &bytes, std::vector<uint32_t> &vec) override;

            asio::ip::udp::endpoint getLastEndpoint() const;
        private:
            void threadInput();
            void threadEcs();
            std::queue<Packet> _queue;
            std::mutex _queueMutex;
            std::condition_variable _cv;

            asio::io_context _io_context;
            asio::ip::udp::socket _socketRead;
            asio::ip::udp::socket _socketSend;
            asio::ip::udp::endpoint _remote_endpoint;
            asio::ip::udp::endpoint _copy_endpoint;

            std::vector<uint32_t> _bufferSerialize;
            std::array<uint32_t, 256> _bufferAsio;
            std::queue<Packet> _queueInput;

            NmpBinary::Binary _binary;
            ProtocoleHandler _ptp;

    };
}