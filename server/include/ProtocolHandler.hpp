#pragma once

#include "Registry.hpp"
#include "Packet.hpp"

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
#include <map>


namespace NmpServer {
    class Server;
    class ProtocoleHandler {
        public:
            ProtocoleHandler(Server &server);
            ~ProtocoleHandler() = default;

            void executeOpCode();
            void fillPacket(Packet &packet);
            void evalMove();
            void evalShoot();
            void evalQuit();
            void evalJoin();

            registry getRegistry() {
                return _ecs;
            }

        private:
            void initPlayer();
            void initEnnemies();
            void initComponents();

            std::reference_wrapper<Server> _refServer;
            registry _ecs;
            Packet _pck;
            std::map<EVENT, std::function<void()>> _mapFctOpCode{
                {{EVENT::MOVE}, [this]{return evalMove();}}, 
                {{EVENT::SHOOT}, [this]{return evalShoot();}}, 
                {{EVENT::QUIT}, [this]{return evalQuit();}}, 
                {{EVENT::JOIN}, [this]{return evalJoin();}}, 
            };
            std::vector<std::pair<Entity, asio::ip::udp::endpoint>> _vecPlayer;
    };
}