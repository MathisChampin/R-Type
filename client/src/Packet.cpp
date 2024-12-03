#include "ClientPacket.hpp"

namespace NmpClient
{
    Packet::Packet(EVENT event, std::optional<DIRECTION> direction) :
        _opCode(event), _arg(direction)
    {
        std::cout << "CLIENT PACKET CREATED" << std::endl;
    }

    Packet::Packet(SpriteInfo &sprite) : _opCode(EVENT::NOTHING), _sprite(sprite)
    {
        std::cout << "SERVER PACKET CREATED" << std::endl;
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

}