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
        std::size_t id = packet.getId();
        int x = packet.getX();
        int y = packet.getY();
        
        if (opcode == NmpServer::EVENT::MOVE) {
            buffer.push_back(static_cast<uint32_t>(opcode));
            buffer.push_back(static_cast<uint32_t>(x));
            buffer.push_back(static_cast<uint32_t>(y));
        }
        if (opcode == NmpServer::EVENT::SPRITE) {
            buffer.push_back(static_cast<uint32_t>(opcode));
            NmpServer::SpriteInfo sprite = packet.getSpriteInfo();
            buffer.push_back(static_cast<uint32_t>(sprite.id));
            buffer.push_back(static_cast<uint32_t>(sprite.x));
            buffer.push_back(static_cast<uint32_t>(sprite.y));
            buffer.push_back(static_cast<uint32_t>(sprite.sizeX));
            buffer.push_back(static_cast<uint32_t>(sprite.sizeY));
        } else if (opcode == NmpServer::EVENT::JOIN) { 
            std::cout << "send id: " << id << std::endl;
            buffer.push_back(static_cast<uint32_t>(opcode));
            buffer.push_back(static_cast<uint32_t>(id));
        }
    }

    NmpServer::Packet Binary::deserialize(std::vector<uint32_t> &buffer)
    {
        std::size_t id = static_cast<std::size_t>(buffer[0]);
        std::cout << "id server deserialize: " << id << std::endl;
        NmpServer::EVENT event = static_cast<NmpServer::EVENT>(buffer[1]);

        if (event == NmpServer::EVENT::MOVE) {
            std::optional<NmpServer::DIRECTION> direction = std::nullopt;
            direction = static_cast<NmpServer::DIRECTION>(buffer[2]);
            this->clearBuffer(buffer);
            return NmpServer::Packet(id, event, direction);
        }
        this->clearBuffer(buffer);
        return NmpServer::Packet(id, event);
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