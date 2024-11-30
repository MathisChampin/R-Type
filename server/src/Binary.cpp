#include "Binary.hpp"

namespace NmpBinary
{
    std::vector<std::string> Binary::getAction(std::string &action)
    {
        std::vector<std::string> buffAction;
        std::size_t posDelim = action.find('/', 0);

        for (; posDelim != std::string::npos; posDelim = action.find('/', posDelim)) {
            buffAction.push_back(action.substr(0, posDelim));
            action.erase(0, ++posDelim);
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

    void Binary::serialize(std::string action, std::vector<uint32_t> &buffer)
    {
        std::vector<std::string> buffAction = getAction(action);

        for (std::string elem : buffAction) {
            std::cout << elem << "\n";
             buffer.push_back(std::stoul(elem));
        }
    }

    std::string Binary::deserialize(std::vector<uint32_t> &buffer)
    {
        std::size_t index{0};
        std::size_t length{buffer.size()};
        std::string result;
        uint8_t octet;

        for (; index != length; index++) {
            octet = getOctets(buffer[index], 0);
            result += std::to_string(octet);

            if (index != length - 1)
                result += "/";
        }

        return result;
    }
}