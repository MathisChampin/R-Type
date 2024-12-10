#pragma once

#include "IClientPacket.hpp"
#include <optional>
#include <iostream>

namespace NmpClient 
{
    class Packet : public IPacket {
        public:
            Packet(std::size_t id, EVENT event, std::optional<DIRECTION> direction = std::nullopt);
            Packet(EVENT event, SpriteInfo &sprites);

            bool checkPacket() override;
            EVENT getOpCode() override;
            std::optional<DIRECTION> getArg() override;
            SpriteInfo getSpriteInfo() override;
            std::size_t getId() override;

        private:
            EVENT _opCode;
            std::optional<DIRECTION> _arg;
            SpriteInfo _sprite;
            std::size_t _id;
    };
}
