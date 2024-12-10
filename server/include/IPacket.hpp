#pragma once

#include "EnumProtocol.hpp"
#include <optional>

namespace NmpServer
{
    class IPacket {
        public:
            virtual bool checkPacket() = 0;
            virtual EVENT getOpCode() = 0;
            virtual std::optional<DIRECTION> getArg() = 0;
            virtual SpriteInfo getSpriteInfo() = 0;
            virtual std::size_t getId() = 0;
            virtual ~IPacket() = default;
    };
}