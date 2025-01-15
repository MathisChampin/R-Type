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

    uint Binary::getOctets(int &code, unsigned int octets)
    {
        uint value{0};

        if (octets == 0 || octets == 8 || octets == 16 || octets == 24)
            value = (code >> 0) & 0xF;
        return value;
    }

    void Binary::serialize(NmpServer::Packet &packet, std::vector<int> &buffer)
    {
        NmpServer::EVENT opcode = packet.getOpCode();
        std::size_t id = packet.getId();
        int x = packet.getX();
        int y = packet.getY();
        
        if (opcode == NmpServer::EVENT::MOVE) {
            buffer.push_back(static_cast<int>(opcode));
            buffer.push_back(static_cast<int>(x));
            buffer.push_back(static_cast<int>(y));
        }
        if (opcode == NmpServer::EVENT::SPRITE) {
            buffer.push_back(static_cast<int>(opcode));
            NmpServer::SpriteInfo sprite = packet.getSpriteInfo();
            buffer.push_back(static_cast<int>(sprite.idClient));
            buffer.push_back(static_cast<int>(sprite.id));
            buffer.push_back(static_cast<int>(sprite.x));
            buffer.push_back(static_cast<int>(sprite.y));
            buffer.push_back(static_cast<int>(sprite.sizeX));
            buffer.push_back(static_cast<int>(sprite.sizeY));
        } else if (opcode == NmpServer::EVENT::JOIN) { 
            std::cout << "Ce negro de lorge: " << id << std::endl;
            buffer.push_back(static_cast<int>(opcode));
            buffer.push_back(static_cast<int>(id));
        } else if (opcode == NmpServer::EVENT::EOI) {
            buffer.push_back(static_cast<int>(opcode));
        } else if (opcode == NmpServer::EVENT::INFO) {
            int life = packet.getLife();
            int score = packet.getScore();
            int level = packet.getLevel();
            buffer.push_back(static_cast<int>(opcode));
            buffer.push_back(static_cast<int>(life));
            buffer.push_back(static_cast<int>(score));
            buffer.push_back(static_cast<int>(level));
        }
    }

    NmpServer::Packet Binary::deserialize(std::vector<int> &buffer)
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

    void Binary::clearBuffer(std::vector<int> &buffer)
    {
        buffer.clear();
    }

    void Binary::printBuffer(std::vector<int> &buffer)
    {
        for (auto elem : buffer) {
            std::cout << "bufferSerialize: " << elem << std::endl;
        }
    }
}