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

    void Binary::serialize(std::string action, std::vector<uint32_t> &buffer)
    {
        for (char c : action) {
            if (c != '/')
                buffer.push_back(static_cast<uint32_t>(c));
        }
    }

    std::string Binary::deserialize(std::vector<uint32_t> &buffer)
    {
        std::string result;
        std::size_t length{buffer.size()};
        std::size_t index{0};

        std::cout << "length: " << length << std::endl;

        for (uint32_t val : buffer) {
            result.push_back(static_cast<char>(val));

            if (index++ != length - 1)
                result.push_back('/');
        }
        return result;
    }
}