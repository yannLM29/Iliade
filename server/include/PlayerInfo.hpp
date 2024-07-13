/**
 * @file PlayerInfo.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <cstdint>

namespace Iliade::Connect
{
    struct PlayerInfo
    {
        int mSessionId = sSessionIDCpt++;
        uint64_t mUId;
        
        std::string mPseudo;

        inline static int sSessionIDCpt = 0;
    };
    
} // namespace Iliade::Connect
