/**
 * @file GameSceneModel.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "core/GameComponentModel.hpp"
#include <iostream>
namespace Iliade
{
    struct GameSceneModel
    {
        int numberOfComponents;
        std::vector<GameComponentModel> mComponents;

        std::vector<uint8_t> serialise()
        {
            std::vector<uint8_t> serialised;

            serialised.emplace_back( mComponents.size() & 0xFF);                               // component list length  (4 bytes)
            serialised.emplace_back((mComponents.size() & 0xFF00) >> 8);                                      
            serialised.emplace_back((mComponents.size() & 0xFF0000) >> 16);
            serialised.emplace_back((mComponents.size() & 0xFF000000) >> 24);

            for(auto &comp : mComponents)                                                // components
            {
                auto comp_serial = comp.serialise();
                for(auto &byte : comp_serial)
                {
                    
                    serialised.emplace_back(byte);
                }
            }

            return std::move(serialised);
        }
    };

} // namespace Iliade

