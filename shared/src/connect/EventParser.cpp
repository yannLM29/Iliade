/**
 * @file EventParser.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "connect/Events/EventParser.hpp"

namespace Iliade::Connect
{
    std::unique_ptr<Event> parseEvent(int16_t eventType, uint32_t size, const std::vector<uint8_t> &dataIn)
    {
        switch (eventType)
        {
        case kNoop:
            return nullptr;
        
        case kStartAnim:
            return std::make_unique<Events::StartAnimEvent>(dataIn);

        case kChangeAnimSpeed:
            return std::make_unique<Events::ChangeAnimSpeed>(dataIn);
        
        case kStopAnim:
            return std::make_unique<Events::StopAnimEvent>(dataIn);

        case kChatMessage:
            return std::make_unique<Events::ChatEvent>(dataIn, size);

        default:
            return nullptr;
        }
    }
} // namespace Iliade::Connect
