/**
 * @file GameComponentModel.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "utils/BitManips.hpp"

namespace Iliade
{
    struct GameComponentModel
    {
        int mId;
        int mType;
        bool mIsPrivate;
        bool mIsStatic;

        std::vector<uint8_t> mData;
        std::vector<GameComponentModel> mChildren;

        std::vector<uint8_t> serialise()
        {
            std::vector<uint8_t> serialised;

            serialised.resize(sizeof(mId) + sizeof(mType));
            std::memcpy(serialised.data(), &mId, sizeof(mId));                          // id           (4 bytes)
            std::memcpy(serialised.data() + sizeof(mId), &mType, sizeof(mType));        // type         (4 bytes)

            serialised.emplace_back(mData.size() & 0xFF);                               // data length  (4 bytes)
            serialised.emplace_back((mData.size() & 0xFF00) >> 8);                                      
            serialised.emplace_back((mData.size() & 0xFF0000) >> 16);
            serialised.emplace_back((mData.size() & 0xFF000000) >> 24);

            for(auto &d : mData)                                                        // data         (data length bytes)
            {
                serialised.emplace_back(d);
            }

            serialised.emplace_back( mChildren.size() & 0xFF);                          // children list length  (4 bytes)
            serialised.emplace_back((mChildren.size() & 0xFF00) >> 8);                                      
            serialised.emplace_back((mChildren.size() & 0xFF0000) >> 16);
            serialised.emplace_back((mChildren.size() & 0xFF000000) >> 24);

            for(auto &child : mChildren)                                                // serialised children
            {
                auto child_serial = child.serialise();
                for(uint8_t &s_byte : child_serial)
                {
                    serialised.emplace_back(s_byte);
                }
            }
            return std::move(serialised);
        }
        
    };
} // namespace Iliade


