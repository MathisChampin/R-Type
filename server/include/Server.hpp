#pragma once

#include "IServer.hpp"
#include "Binary.hpp"
#include "ProtocolHandler.hpp"
#include "Registry.hpp"
#include <mutex>
#include <queue>
#include <thread>
#include <chrono>
#include <map>
#include <atomic>

namespace NmpServer {
    class Server : public IServer {
        public:
            Server();
            ~Server();

            void run() override;
            void get_data() override;
            void send_data(Packet &packet, asio::ip::udp::endpoint enpoint) override;
            void extract_bytes(std::size_t &bytes, std::vector<uint32_t> &vec) override;
            void broadcast(Packet &packet) override;
            asio::ip::udp::endpoint getLastEndpoint() const;
            void sendScore(int i, sparse_array<component::life> &lifes, sparse_array<component::attribute> &attributes);

            std::vector<asio::ip::udp::endpoint> _vecPlayer;
        private:
            void threadInput();
            void threaEvalInput();
            void threadSystem();
            void threadShootEnnemies();
            void send_entity(registry &);
            void notifyShoot();

            uint32_t getId(component::attribute &att);

            std::atomic<bool> _running;
            bool _shootReady;
            std::queue<Packet> _queue;
            std::mutex _queueMutex;
            std::mutex _ecsMutex;
            std::mutex _playerMutex;
            std::condition_variable _cv;
            std::condition_variable _cvShoot;
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