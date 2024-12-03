#include "Binary.hpp"

namespace NmpBinary
{
    std::vector<std::string> Binary::getAction(std::string &action)
    {
        std::vector<std::string> buffAction;
        std::size_t posDelim = action.find('/', 0);

        for (; posDelim != std::string::npos; posDelim = action.find('/', posDelim)) {
            buffAction.push_back(action.substr(0, posDelim));
            action.erase(0, posDelim + 1);
        }

        buffAction.push_back(action.substr(0, posDelim));
        return buffAction;
    }

    uint8_t Binary::getOctets(uint32_t &code, unsigned int octets)
    {
        uint8_t value{0};

        if (octets == 0 || octets == 8 || octets == 16 || octets == 24)
            value = (code >> 0) & 0xF;
        return value;
    }

    void Binary::serialize(NmpServer::Packet &packet, std::vector<uint32_t> &buffer)
    {
        NmpServer::EVENT opcode = packet.getOpCode();

        buffer.push_back(static_cast<uint32_t>(opcode));

        if (opcode == NmpServer::EVENT::MOVE)
            buffer.push_back(static_cast<uint32_t>(opcode));

        if (opcode == NmpServer::EVENT::NOTHING) {
            NmpServer::SpriteInfo sprite = packet.getSpriteInfo();
            buffer.push_back(sprite.id);
            buffer.push_back(sprite.x);
            buffer.push_back(sprite.y);
            buffer.push_back(sprite.sizeX);
            buffer.push_back(sprite.sizeY);
        }
    }

    NmpServer::Packet Binary::deserialize(std::vector<uint32_t> &buffer)
    {
        NmpServer::EVENT event = static_cast<NmpServer::EVENT>(buffer[0]);

        if (event == NmpServer::EVENT::MOVE) {
            std::optional<NmpServer::DIRECTION> direction = std::nullopt;
            direction = static_cast<NmpServer::DIRECTION>(buffer[1]);
            return NmpServer::Packet(event, direction);
        }
        if (event == NmpServer::EVENT::NOTHING) {
            NmpServer::SpriteInfo sprite = {
                buffer[2],
                buffer[3],
                buffer[4],
                buffer[5],
                buffer[6] 
            };
            return NmpServer::Packet(NmpServer::EVENT::NOTHING, sprite);
        }
        return NmpServer::Packet(event);
    }

    void Binary::clearBuffer(std::vector<uint32_t> &buffer)
    {
        buffer.clear();
    }

    void Binary::printBuffer(std::vector<uint32_t> &buffer)
    {
        for (auto elem : buffer) {
            std::cout << "bufferSerialize: " << elem << std::endl;
        }
    }
}