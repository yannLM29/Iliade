/**
 * @file Event.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <memory>
#include "connect/Events/EventTypes.hpp"
#include "utils/BitManips.hpp"

namespace Iliade::Connect
{
    class Event
    {
    private:
        uint16_t mType;      // uint16_t
        uint32_t mSize;

    public:
        Event(eEventTypes type, uint32_t size) : mType(type), mSize(size + 6)
        {

        }
        
        // ~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~
        inline uint16_t getType() const noexcept
        {
            return mType;
        }

        inline uint32_t getSize() const noexcept
        {
            return mSize;
        }

        inline void setType(eEventTypes type) noexcept
        {
            mType = type;
        }

        inline void setSize(int size) noexcept
        {
            mSize = size;
        }

        // ~~~~~~~~~~~~~~~~ SERIALISE ~~~~~~~~~~~~~~~~
        virtual std::vector<uint8_t> serialise() const noexcept
        {
            std::vector<uint8_t> r;
            addValueToByteVector(mType, r);
            addValueToByteVector(mSize, r);

            return r;
        }


        static std::unique_ptr<Event> deserialise(const std::vector<uint8_t> &data, int &outEventType);
        
    };
    
    
} // namespace Iliade::Connect
