#pragma once

#include "IPacket.hpp"
#include <optional>
#include <iostream>

namespace NmpServer
{
    class Packet : public IPacket {
        public:
            Packet() = default;
            Packet(EVENT event, std::optional<DIRECTION> direction = std::nullopt);
            Packet(EVENT event, SpriteInfo &sprites);

            Packet& operator=(const Packet &other);

            bool checkPacket() override;
            EVENT getOpCode() override;
            std::optional<DIRECTION> getArg() override;
            SpriteInfo getSpriteInfo() override;

        private:
            EVENT _opCode;
            std::optional<DIRECTION> _arg;
            SpriteInfo _sprite;
    };
}
