/**
 * @file ChatEvents.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>

#include "Event.hpp"
#include "utils/BitManips.hpp"


namespace Iliade::Connect::Events
{
    class ChatEvent : public Event
    {
    private:
        std::string mMessage;
        std::string mPseudo;
    
    public:
        ChatEvent(const std::string &message, const std::string &pseudo = "") : Event(kChatMessage, message.size() + pseudo.size() + 8), mMessage(message), mPseudo(pseudo)
        {

        }

        ChatEvent(const std::vector<uint8_t> &dataIn, uint32_t size) : Event(kChatMessage, size)
        {
            int offset = 0;

            uint32_t messageSize = readUInt32ValueFromByteVector(dataIn.begin() + 0);
            offset += 4;

            mMessage = readStringValueFromBytePointer(dataIn.begin() + offset, dataIn.begin() + offset + messageSize);
            offset += messageSize;

            uint32_t pseudoSize = readUInt32ValueFromByteVector(dataIn.begin() + offset);
            offset += 4;

            mPseudo = readStringValueFromBytePointer(dataIn.begin() + offset, dataIn.begin() + offset + pseudoSize);
            setSize(offset + pseudoSize);
        }

        // ~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~
        inline const std::string &getMessage() const noexcept
        {
            return mMessage;
        }

        inline const std::string &getPseudo() const noexcept
        {
            return mPseudo;
        }

        // ~~~~~~~~~~~~~~~~ SERIALISE ~~~~~~~~~~~~~~~~
        std::vector<uint8_t> serialise() const noexcept
        {
            std::vector<uint8_t> r = Event::serialise();
            addValueToByteVector(static_cast<uint32_t>(mMessage.size()), r);
            addValueToByteVector(mMessage, r);
            addValueToByteVector(static_cast<uint32_t>(mPseudo.size()), r);
            addValueToByteVector(mPseudo, r);

            return std::move(r);
        }
    };
    
    
} // namespace Iliade::Connect
