#include "../include/client/ClientBinary.hpp"

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

     void Binary::serialize(NmpClient::Packet &packet, std::vector<uint32_t> &buffer)
    {
        NmpClient::EVENT opcode = packet.getOpCode();
        std::size_t id = packet.getId();

        buffer.push_back(static_cast<uint32_t>(id));
        buffer.push_back(static_cast<uint32_t>(opcode));

        if (opcode == NmpClient::EVENT::MOVE) {
            NmpClient::DIRECTION direction = packet.getArg().value();
            buffer.push_back(static_cast<uint32_t>(direction));
        }
    }

    NmpClient::Packet Binary::deserialize(std::vector<uint32_t> &buffer)
    {
        NmpClient::EVENT event = static_cast<NmpClient::EVENT>(buffer[0]);

        if (event == NmpClient::EVENT::MOVE) {
            int x = static_cast<int>(buffer[1]);
            int y = static_cast<int>(buffer[2]);
            return NmpClient::Packet(event, x, y);
        }
        if (event == NmpClient::EVENT::SPRITE) {
            NmpClient::SpriteInfo sprite = {
                buffer[1],
                buffer[2],
                buffer[3],
                buffer[4],
                buffer[5]};
            return NmpClient::Packet(NmpClient::EVENT::SPRITE, sprite);
        } else {
            std::size_t id = static_cast<std::size_t>(buffer[1]);
            return NmpClient::Packet(id, event);
        }
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