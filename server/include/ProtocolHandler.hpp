#pragma once

#include "Registry.hpp"
#include "position.hpp"
#include "Packet.hpp"
#include <iostream>
#include <map>


namespace NmpServer {
    class ProtocoleHandler {
        public:
            ProtocoleHandler();
            ~ProtocoleHandler() = default;

            void executeOpCode();
            void fillPacket(Packet &packet);
            void evalMove();
            void evalShoot();
            void evalQuit();

        private:
            registry _ecs;
            Packet _pck;
            std::map<EVENT, std::function<void()>> _mapFctOpCode{
                {{EVENT::MOVE}, [this]{return evalMove();}}, 
                {{EVENT::SHOOT}, [this]{return evalShoot();}}, 
                {{EVENT::QUIT}, [this]{return evalQuit();}}, 
            };
    };
}