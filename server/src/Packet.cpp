#include "Packet.hpp"

namespace NmpServer
{
    Packet::Packet(EVENT event, std::optional<DIRECTION> direction) :
        _opCode(event), _arg(direction)
    {
        std::cout << "SERVER packet input created" << std::endl;
    }

    Packet::Packet(EVENT event, SpriteInfo &sprite) : _opCode(event), _sprite(sprite)
    {
        std::cout << "SERVER packet sprite created" << std::endl;
    }

    bool Packet::checkPacket()
    {
        if (_opCode != EVENT::MOVE && _opCode != EVENT::SHOOT && _opCode != EVENT::QUIT) {
            return false;
        }

        if (_opCode == EVENT::MOVE) {
            if (!_arg.has_value()) {
                return false;
            }

            DIRECTION direction = _arg.value();
            if (direction != DIRECTION::LEFT && direction != DIRECTION::RIGHT &&
                direction != DIRECTION::UP && direction != DIRECTION::DOWN) {
                return false;
            }
        }

        if ((_opCode == EVENT::SHOOT || _opCode == EVENT::QUIT) && _arg.has_value()) {
            return false;
        }

        return true;
    }

    EVENT Packet::getOpCode()
    {
        return _opCode;
    }

    std::optional<DIRECTION> Packet::getArg()
    {
        return _arg;
    }

    SpriteInfo Packet::getSpriteInfo()
    {
        return _sprite;
    }

    Packet& Packet::operator=(const Packet &other) {
        if (this == &other)
            return *this;

        this->_opCode = other._opCode;
        this->_arg = other._arg;
        this->_sprite = other._sprite;

        return *this;
    }
}