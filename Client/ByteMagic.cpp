#include "ByteMagic.h"

unsigned int byteOrderSwap(unsigned int num)
{
    return (num >> 24) |
        ((num << 8) & 0x00FF0000) |
        ((num >> 8) & 0x0000FF00) |
        (num << 24);
}

std::vector<unsigned char> intToBytesBE(unsigned int num)
{
    std::vector<unsigned char> ret(sizeof(num));
    for (size_t i = 0; i < sizeof(num); i++)
    {
        ret[i] = (num >> (CHAR_BIT * (3-i))) & 0xff;
    }
    return ret;
}

long long MACStringToLong(const std::string& str)
{
    if (str.size() != MAC_ADDR_STR_SIZE)
    {
        throw std::runtime_error("Invalid MAC address size (" + str + "): " + std::to_string(str.size()) + " != " + std::to_string(MAC_ADDR_STR_SIZE));
    }

    std::istringstream iss(str);
    uint64_t b;
    uint64_t result(0);
    iss >> std::hex;
    while (iss >> b) {
        result = (result << 8) + b;
        auto eaten = iss.get();
        if (eaten != '-' && eaten != ':')
        {
            throw std::runtime_error("Invalid MAC address format: " + str);
        }
    }
    return result;
}

