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
            Server(const Difficulty difficulty, const bool friendlyFire);
            ~Server();

            void run() override;
            void get_data() override;
            void send_data(Packet &packet, asio::ip::udp::endpoint enpoint) override;
            void extract_bytes(std::size_t &bytes, std::vector<int> &vec) override;
            void broadcast(Packet &packet) override;
            void sendScoreLife(int i, component::state &st);
            void stop();
            void killSocket();
            asio::ip::udp::endpoint getLastEndpoint() const;

            std::vector<asio::ip::udp::endpoint> _vecPlayer;
        private:
            void threadInput();
            void threaEvalInput();
            void threadSystem();
            void delaySpawn(ClockManager &c);
            bool isLevelReady();
            void send_entity();
            bool check_level(registry &);
            bool check_level_player(registry &);
            void copyEcs();
            int getId(component::attribute &att);
            void pauseThreads();
            void resumeThreads();
            int getLenVecPLayer();

            int _sizePlayer;
            int _playerLose;
            Difficulty _difficulty;
            bool _friendlyFire;
            std::atomic<bool> _paused{false};
            std::mutex _pauseMutex;
            std::condition_variable _pauseCv;
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

            std::map<component::attribute::entityType, int> _mapSpriteID = {
                {component::attribute::Player1, 1},
                {component::attribute::Player2, 1},
                {component::attribute::Player3, 1},
                {component::attribute::Player4, 1},
                {component::attribute::Ennemies, 2},
                {component::attribute::Ennemies2, 3},
                {component::attribute::Ennemies3, 4},
                {component::attribute::Ennemies4, 5},
                {component::attribute::Ennemies5, 6},
                {component::attribute::Shoot, 7},
                {component::attribute::Shoot2, 8},
                {component::attribute::Shoot3, 9},
                {component::attribute::Shoot4, 10},
                {component::attribute::PowerUpLife, 11},
                {component::attribute::PowerUpMove, 12},
                {component::attribute::Shoot5, 13},
                {component::attribute::Shoot6, 14},
                {component::attribute::Shoot7, 15},
                {component::attribute::Shoot8, 16},
                {component::attribute::Shoot9, 17},
                {component::attribute::Shoot10, 18},
                {component::attribute::Shoot1, 19},
            };
            std::vector<NmpServer::infoEnnemies_t> _vecSpawn;

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