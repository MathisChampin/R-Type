#include "../include/client/ClientPacket.hpp"

namespace NmpClient
{
    Packet::Packet(std::size_t id, EVENT event, std::optional<DIRECTION> direction) :
        _opCode(event), _arg(direction), _id(id)
    {
        std::cout << "CLIENT packet input created for id: " << _id <<  std::endl;
    }

    Packet::Packet(EVENT event, SpriteInfo &sprite) : _opCode(event), _sprite(sprite)
    {
        std::cout << "CLIENT packet sprite created" << std::endl;
    }

    Packet::Packet(EVENT event, int x, int y) :
        _opCode(event), _x(x), _y(y)
    {
        std::cout << "CLIENT packet pos created" <<  std::endl;
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

    std::size_t Packet::getId()
    {
        return _id;
    }

    int Packet::getX() const
    {
        return _x;
    }

    int Packet::getY() const
    {
        return _y;
    }

}