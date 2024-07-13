/**
 * @file EventTypes.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <cstdint>

namespace Iliade::Connect
{
    enum eEventTypes : uint16_t {
        kNoop = 0,
        kStartAnim,
        kChangeAnimSpeed,
        kStopAnim,
        kChatMessage
    };
} // namespace Iliade::Connect
