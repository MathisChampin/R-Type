#pragma once

#include "IServer.hpp"
#include "Binary.hpp"
#include "ProtocolHandler.hpp"
#include "ProceduralLevel.hpp"
#include "ClockManager.hpp"
#include "Registry.hpp"
#include "Parser.hpp"
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
            void extract_bytes(std::size_t &bytes, std::vector<int> &vec) override;
            void broadcast(Packet &packet) override;
            asio::ip::udp::endpoint getLastEndpoint() const;
            void sendScoreLife(int i);

            std::vector<asio::ip::udp::endpoint> _vecPlayer;
        private:
            void threadInput();
            void threaEvalInput();
            void threadSystem();
            void delaySpawn(ClockManager &c, bool &srpiteAdded);
            void send_entity();
            bool check_level(registry &);
            bool check_level_player(registry &);
            void copyEcs();
            std::vector<NmpServer::infoEnnemies_t> _vecSpawn;

            int getId(component::attribute &att);

            std::atomic<bool> _running;
            bool _shootReady;
            std::queue<Packet> _queue;
            std::mutex _mutexPtp;
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

            std::vector<int> _bufferSerialize;
            std::array<int, 256> _bufferAsio;
            std::queue<Packet> _queueInput;

            NmpBinary::SBinary _binary;
            ProtocoleHandler _ptp;
            Parser _parser;
            ProceduralLevel _prodLevel;

            sparse_array<component::position> _positions;
            sparse_array<component::state> _states;
            sparse_array<component::size> _sizes;
            sparse_array<component::attribute> _attributes;
            sparse_array<component::level> _levels;
            sparse_array<component::life> _lifes;
            sparse_array<component::score> _scores;
            registry _ecs;
    };
}