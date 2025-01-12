#pragma once

#include "Registry.hpp"
#include "Packet.hpp"
#include "Parser.hpp"

#include "attribute.hpp"
#include "controllable.hpp"
#include "level.hpp"
#include "life.hpp"
#include "position.hpp"
#include "score.hpp"
#include "size.hpp"
#include "state.hpp"
#include "velocity.hpp"
#include "system.hpp"

#include <functional>
#include <iostream>
#include <asio.hpp>
#include <utility>
#include <random>
#include <chrono>
#include <map>


namespace NmpServer {
    class Server;
    class ProtocoleHandler {
        public:
            ProtocoleHandler(Server &server);
            ~ProtocoleHandler() = default;

            void executeOpCode();
            void fillPacket(Packet &packet);
            registry &getECS();
            std::vector<std::pair<Entity, asio::ip::udp::endpoint>> &get_vector() {
                return _vecPlayer;
            }

            void loadEnnemiesFromconfig(const std::vector<infoEnnemies_t> vecEnnemies);
            void clearPlayer();
    
        private:
            void evalMove();
            void evalQuit();
            void evalJoin();

            void initPlayer();
            void initComponents();
            void initEnnemies(int posX, int posY, int type);
            void joinNewLevel(asio::ip::udp::endpoint ip);
        
            void updateMoveEcs(Entity &player, component::controllable::Key &control, sparse_array<component::position>::value_type &pos, component::attribute &att);
            std::optional<asio::ip::udp::endpoint> foundEndpointByClient(Entity &player);
            uint32_t getId(component::attribute &att);

            std::reference_wrapper<Server> _refServer;
            registry _ecs;
            Packet _pck;
            std::map<EVENT, std::function<void()>> _mapFctOpCode{
                {{EVENT::MOVE}, [this]{return evalMove();}}, 
                {{EVENT::QUIT}, [this]{return evalQuit();}},
                {{EVENT::JOIN}, [this]{return evalJoin();}}, 
            };
            std::vector<std::pair<Entity, asio::ip::udp::endpoint>> _vecPlayer;
            std::chrono::steady_clock::time_point _lastEnemyCreationTime;
            std::chrono::steady_clock::time_point _lastShootCreationTime;
            int _nbPlayer{0};
    };
}