#include "../include/client/ClientBinary.hpp"

namespace NmpBinary
{
    std::vector<std::string> Binary::getAction(std::string &action)
    {
        std::vector<std::string> buffAction;
        std::size_t posDelim = action.find('/', 0);

        for (; posDelim != std::string::npos; posDelim = action.find('/', posDelim))
        {
            buffAction.push_back(action.substr(0, posDelim));
            action.erase(0, posDelim + 1);
        }

        buffAction.push_back(action.substr(0, posDelim));
        return buffAction;
    }


    void Binary::serialize(NmpClient::Packet &packet, std::vector<int> &buffer)
    {
        NmpClient::EVENT opcode = packet.getOpCode();
        std::size_t id = packet.getId();

        std::cout << "id serialize: " << id << std::endl;
        std::cout << static_cast<int>(opcode) << std::endl;
        buffer.push_back(static_cast<int>(id));
        buffer.push_back(static_cast<int>(opcode));

        if (opcode == NmpClient::EVENT::MOVE)
        {
            NmpClient::DIRECTION direction = packet.getArg().value();
            std::cout << static_cast<int>(direction) << std::endl;

            buffer.push_back(static_cast<int>(direction));
        }
    }

    NmpClient::Packet Binary::deserializes(std::vector<int> &buffer)
    {
        NmpClient::EVENT event = static_cast<NmpClient::EVENT>(buffer[0]);

        if (event == NmpClient::EVENT::MOVE)
        {
            int x = static_cast<int>(buffer[1]);
            int y = static_cast<int>(buffer[2]);
            return NmpClient::Packet(event, x, y, 0);
        }
        else if (event == NmpClient::EVENT::SPRITE)
        {
            NmpClient::SpriteInfo sprite = {
                static_cast<int>(buffer[1]),
                static_cast<int>(buffer[2]),
                static_cast<int>(buffer[3]),
                static_cast<int>(buffer[4]),
                static_cast<int>(buffer[5]),
                static_cast<int>(buffer[6])};
            return NmpClient::Packet(NmpClient::EVENT::SPRITE, sprite);
        }
        else if (event == NmpClient::EVENT::JOIN)
        {
            std::size_t id = static_cast<std::size_t>(buffer[1]);
            return NmpClient::Packet(id, event);
        } 
        else if (event == NmpClient::EVENT::EOI) {
            return NmpClient::Packet(NmpClient::EVENT::EOI);
        } 
        else if (event == NmpClient::EVENT::INFO) {
            int life = static_cast<int>(buffer[1]);
            int score = static_cast<int>(buffer[2]);
            int level = static_cast<int>(buffer[3]);
            return NmpClient::Packet(NmpClient::EVENT::INFO, life, score, level);
        }
        return NmpClient::Packet(event, 0,0,0);
    }

    void Binary::clearBuffer(std::vector<int> &buffer)
    {
        buffer.clear();
    }

    void Binary::printBuffer(std::vector<int> &buffer)
    {
        for (auto elem : buffer)
        {
            std::cout << "bufferSerialize: " << elem << std::endl;
        }
    }
}