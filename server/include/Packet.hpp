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
            // Packet(EVENT event, int x, int y);
            Packet(EVENT event, SpriteInfo &sprites);
            Packet(EVENT event);
            /**
             * @brief Constructs a Packet object.
             *
             * @param event The event associated with the packet.
             * @param elem the info to print score or life.
             */
            Packet(EVENT event, int life, int score, int level);

            Packet& operator=(const Packet &other);

            bool checkPacket() override;
            EVENT getOpCode() override;
            std::optional<DIRECTION> getArg() override;
            SpriteInfo getSpriteInfo() override;
            std::size_t getId() override;
            
            int getX() const;
            int getY() const;
            int getLife() const;
            int getScore() const;
            int getLevel() const;

        private:
            EVENT _opCode;
            std::optional<DIRECTION> _arg;
            SpriteInfo _sprite;
            std::size_t _id;
            int _x{0};
            int _y{0};
            int _life{0};
            int _score{0};
            int _level{0};
    };
}
