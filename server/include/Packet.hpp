#pragma once

#include "IPacket.hpp"
#include <optional>
#include <iostream>

namespace NmpServer
{
    class Packet : public IPacket {
        public:
            Packet() = default;
            Packet(std::size_t id, EVENT event, std::optional<DIRECTION> direction = std::nullopt);
            Packet(EVENT event, SpriteInfo &sprites);

            Packet& operator=(const Packet &other);

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
