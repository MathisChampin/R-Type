#pragma once

#include "IClientPacket.hpp"
#include <optional>
#include <iostream>

namespace NmpClient 
{
    class Packet : public IPacket {
        public:
            Packet(std::size_t id, EVENT event, std::optional<DIRECTION> direction = std::nullopt);
            Packet(EVENT event, int x, int y);
            Packet(EVENT event, SpriteInfo &sprites);
            std::optional<DIRECTION> getDirection() const;

            bool checkPacket() override;
            EVENT getOpCode() override;
            std::optional<DIRECTION> getArg() override;
            SpriteInfo getSpriteInfo() override;
            std::size_t getId() override;

            int getX() const;
            int getY() const;

        private:
            EVENT _opCode;
            std::optional<DIRECTION> _arg;
            SpriteInfo _sprite;
            std::size_t _id;
            int _x{0};
            int _y{0};
    };
}
