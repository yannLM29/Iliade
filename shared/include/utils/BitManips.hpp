/**
 * @file BitManips.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace Iliade
{
    /**
     * @brief 
     * @warning LSB
     * @param value 
     * @param byteVector 
     */

    void addValueToByteVector(uint8_t value, std::vector<uint8_t> &byteVector);
    void addValueToByteVector(uint16_t value, std::vector<uint8_t> &byteVector);
    void addValueToByteVector(int32_t value, std::vector<uint8_t> &byteVector);
    void addValueToByteVector(uint32_t value, std::vector<uint8_t> &byteVector);
    void addValueToByteVector(float value, std::vector<uint8_t> &byteVector);
    void addValueToByteVector(double value, std::vector<uint8_t> &byteVector);
    void addValueToByteVector(const std::string &value, std::vector<uint8_t> &byteVector);

    int16_t readInt16ValueFromByteVector(std::vector<uint8_t>::const_iterator it);
    int32_t readInt32ValueFromByteVector(std::vector<uint8_t>::const_iterator it);
    uint32_t readUInt32ValueFromByteVector(std::vector<uint8_t>::const_iterator it);
    float readFloatValueFromByteVector(std::vector<uint8_t>::const_iterator it);
    float readFloatValueFromBytePointer(uint8_t *p);
    std::string readStringValueFromBytePointer(std::vector<uint8_t>::const_iterator it_begin, std::vector<uint8_t>::const_iterator it_end);


} // namespace Iliade
