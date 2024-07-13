/**
 * @file GameAsset.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-04-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "core/GameComponent.hpp"

namespace Iliade
{
    class GameAsset : public GameComponent
    {
    private:
        /* data */
    public:
        GameAsset(GameScene &scene) : GameComponent(scene) {}
        GameAsset(GameComponent *parentComponent) : GameComponent(parentComponent) {}
        ~GameAsset() {};

        int getType() override
        {
            return UNIQUE_COMPONENT_TYPE_ID;
        }
    };
    
    
} // namespace Iliade
