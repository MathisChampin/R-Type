#include "ProtocolHandler.hpp"

namespace NmpServer
{
    void ProtocoleHandler::executeOpCode()
    {
        EVENT key = _pck.getOpCode();
        auto it = _mapFctOpCode.find(key);
        if (it != _mapFctOpCode.end()) {
            it->second();
        }
    }

    ProtocoleHandler::ProtocoleHandler()
    {
        std::cout << "protocole Handler create" << std::endl;
    }

    void ProtocoleHandler::fillPacket(Packet &packet)
    {
        _pck = packet;
    }

    void ProtocoleHandler::evalMove()
    {
        std::cout << "evalMove" << std::endl;
        auto direction = _pck.getArg();
            if (direction.has_value())
                std::cout << "Direction: ";
            if (direction == DIRECTION::DOWN)
                std::cout << "DOWN" << std::endl;
            else if (direction == DIRECTION::UP)
                std::cout << "UP" << std::endl;
            else if (direction == DIRECTION::LEFT)
                std::cout << "LEFT" << std::endl;
            else if (direction == DIRECTION::RIGHT)
                std::cout << "RIGHT" << std::endl;
            else
                std::cout << "NO DIRECTION" << std::endl;
    }

    void ProtocoleHandler::evalShoot()
    {
        std::cout << "evalShoot" << std::endl;
    }

    void ProtocoleHandler::evalQuit()
    {
        std::cout << "evalQuit" << std::endl;
    }

    void ProtocoleHandler::evalJoin()
    {
        std::cout << "evalJoin" << std::endl;
    }

}