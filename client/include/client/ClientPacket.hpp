#pragma once

#include "IClientPacket.hpp"
#include <optional>
#include <iostream>

namespace NmpClient
{
    class Packet : public IPacket {
        public:
        Packet() = default;
           /**
         * @brief Constructs a Packet object.
         *
         * @param id The unique identifier for the packet.
         * @param event The event associated with the packet.
         * @param direction Optional direction associated with the packet. Defaults to std::nullopt.
         */
            Packet(std::size_t id, EVENT event, std::optional<DIRECTION> direction = std::nullopt);
            Packet(EVENT event);
            std::optional<DIRECTION> getDirection() const;

        /**
         * @brief Constructs a Packet object.
         *
         * @param id The unique identifier for the packet.
         * @param event The event associated with the packet.
         * @param x The x-coordinate associated with the packet.
         * @param y The y-coordinate associated with the packet.
         */
        Packet(EVENT event, int x, int y);

        /**
         * @brief Constructs a Packet object.
         *
         * @param event The event associated with the packet.
         * @param sprites The sprite information associated with the packet.
         */
        Packet(EVENT event, SpriteInfo &sprites);

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
