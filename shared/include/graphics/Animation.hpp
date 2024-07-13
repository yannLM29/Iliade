/**
 * @file Animation.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <vector>

#include "graphics/Frame.hpp"

namespace Iliade::Graphics
{
    struct Animation
    {
        std::vector<Frame> frames;
    };
    
} // namespace Iliade::Graphics
