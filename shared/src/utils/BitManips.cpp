#include "utils/BitManips.hpp"

#include <iostream>
#include <cstring>

namespace Iliade
{

    void addValueToByteVector(uint8_t value, std::vector<uint8_t> &byteVector)
    {
        byteVector.emplace_back(value);
    }

    void addValueToByteVector(uint16_t value, std::vector<uint8_t> &byteVector)
    {
        byteVector.emplace_back( value & 0xFF);
        byteVector.emplace_back((value & 0xFF00) >> 8);                                      
    }

    void addValueToByteVector(int32_t value, std::vector<uint8_t> &byteVector)
    {
        byteVector.emplace_back( value & 0xFF);                               // data length  (4 bytes)
        byteVector.emplace_back((value & 0xFF00) >> 8);                                      
        byteVector.emplace_back((value & 0xFF0000) >> 16);
        byteVector.emplace_back((value & 0xFF000000) >> 24);
    }

    void addValueToByteVector(uint32_t value, std::vector<uint8_t> &byteVector)
    {
        byteVector.emplace_back( value & 0xFF);                               // data length  (4 bytes)
        byteVector.emplace_back((value & 0xFF00) >> 8);                                      
        byteVector.emplace_back((value & 0xFF0000) >> 16);
        byteVector.emplace_back((value & 0xFF000000) >> 24);
    }

    void addValueToByteVector(float value, std::vector<uint8_t> &byteVector)
    {
        byteVector.resize(byteVector.size() + sizeof(float));
        auto whereToWrite = byteVector.end() - sizeof(float);

        std::memcpy(whereToWrite.base(), &value, sizeof(float));
    }

    void addValueToByteVector(double value, std::vector<uint8_t> &byteVector)
    {
        
    }

    void addValueToByteVector(const std::string &value, std::vector<uint8_t> &byteVector)
    {
        for(const auto &c : value)
        {
            byteVector.emplace_back(c);
        }
    }


    bool readBoolValueFromByteVector(std::vector<uint8_t>::const_iterator it)
    {
        uint8_t r;
        memcpy(&r, it.base(), sizeof(uint8_t));
        return r != 0 ? true : false; 
    }

    int16_t readInt16ValueFromByteVector(std::vector<uint8_t>::const_iterator it)
    {
        int16_t r;
        memcpy(&r, it.base(), sizeof(int16_t));
        return r; 
    }

    int32_t readInt32ValueFromByteVector(std::vector<uint8_t>::const_iterator it)
    {
        int32_t r;
        memcpy(&r, it.base(), sizeof(int32_t));
        return r; 
    }

    uint32_t readUInt32ValueFromByteVector(std::vector<uint8_t>::const_iterator it)
    {
        uint32_t r;
        memcpy(&r, it.base(), sizeof(int32_t));
        return r; 
    }

    float readFloatValueFromByteVector(std::vector<uint8_t>::const_iterator it)
    {
        float r;
        memcpy(&r, it.base(), sizeof(float));

        return r;
    }

    float readFloatValueFromBytePointer(uint8_t *p)
    {
        float r;
        memcpy(&r, p, sizeof(float));

        return r;
    }

    std::string readStringValueFromBytePointer(std::vector<uint8_t>::const_iterator it_begin, std::vector<uint8_t>::const_iterator it_end)
    {
        std::string r = "";
        for(auto it = it_begin; it != it_end; it++)
        {
            r += static_cast<char>(*it);
        }   
        return std::move(r);
    }

} // namespace Iliade

