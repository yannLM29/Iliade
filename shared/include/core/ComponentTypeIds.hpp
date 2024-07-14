/**
 * @file ComponentTypeIds.hpp
 * @author Yann Le Masson
 * @brief Enum of components types
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

namespace Iliade
{
    enum eComponentType : int {
        kGameComponent = 0,
        kGameElement,
        kPlayableElement,
        kSpriteAsset
    };
    
} // namespace Iliade

