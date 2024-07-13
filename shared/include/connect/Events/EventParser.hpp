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
#pragma once

#include <memory>

#include "connect/Events/Event.hpp"
#include "connect/Events/ChatEvents.hpp"
#include "connect/Events/AnimationEvents.hpp"

namespace Iliade::Connect
{
    std::unique_ptr<Event> parseEvent(int16_t eventType, uint32_t size, const std::vector<uint8_t> &dataIn);
    
} // namespace Iliade::Connect
