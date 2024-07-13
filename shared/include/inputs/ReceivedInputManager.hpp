/**
 * @brief 
 * 
 */

#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

#include "inputs/InputEvent.hpp"
#include "utils/BitManips.hpp"

namespace Iliade::Inputs
{
    class ReceivedInputManager
    {
    private:
        std::vector<InputEvent> mEvents;
        std::array<uint16_t, eInputCode::length> mInputState;
        int mLocalMousePositionX, mLocalMousePositionY;
        int mGlobalMousePositionX, mGlobalMousePositionY;

    public:
        ReceivedInputManager(/* args */)
        {

        }


        inline uint16_t getGlobalMousePositionX() const noexcept
        {
            return mGlobalMousePositionX;
        }
        inline uint16_t getGlobalMousePositionY() const noexcept
        {
            return mGlobalMousePositionY;
        }
        inline uint16_t getLocalMousePositionX() const noexcept
        {
            return mLocalMousePositionX;
        }
        inline uint16_t getLocalMousePositionY() const noexcept
        {
            return mLocalMousePositionY;
        }

        /**
         * @brief Need to be rework to be more optimized and to handle analog controls
        */
        void parseInputData(const std::vector<uint32_t> &data)
        {

            // Check if an input is not twice in the data
            std::vector<uint16_t> codes;

            for(const auto &input : data)
            {
                uint16_t code = (input & 0xFFFF0000) >> 16;
                
                auto codesIt = std::find_if(codes.cbegin(), codes.cend(), [&](const auto &c){
                    return c == code;
                });

                if(codesIt != codes.cend())
                {
                    // error two times same input;
                    return;
                }

                codes.emplace_back((input & 0xFF00) >> 16);
            }

            
            std::vector<uint32_t> newPressed;
            std::vector<uint32_t> StillPressed;
            std::vector<InputEvent> newReleased;


            for(const auto& dataEvent : data)
            {
                uint16_t code = static_cast<uint16_t>((dataEvent & 0xFFFF0000) >> 16);
                uint16_t value = static_cast<uint16_t>(dataEvent & 0x0000FFFF);

                if(code == kMousePosX)
                {
                    mLocalMousePositionX = value;
                    continue;
                }
                if(code == kMousePosY)
                {
                    mLocalMousePositionY = value;
                    continue;
                }
                if(code == kGlobalMousePosX)
                {
                    mGlobalMousePositionX = value;
                    continue;
                }
                if(code == kGlobalMousePosY)
                {
                    mGlobalMousePositionY = value;
                    continue;
                }

                auto codeCompare = [&](const InputEvent &event){
                    return event.code == code && (event.status == kPressed || event.status == kStillPressed);
                };


                if(std::find_if(mEvents.cbegin(), mEvents.cend(), codeCompare) != mEvents.cend())
                {
                    StillPressed.emplace_back(dataEvent);
                }
                else
                {
                    newPressed.emplace_back(dataEvent);
                }
            }

            for(const auto &event : mEvents)
            {
                if(event.status == kPressed || event.status == kStillPressed)
                {
                    if(std::find_if(data.cbegin(), data.cend(), [&](const uint32_t& dataEvent){
                        uint16_t code = static_cast<uint16_t>((dataEvent & 0xFFFF0000) >> 16);
                        return event.code == code;
                    }) == data.cend())
                    {
                        newReleased.emplace_back(event);
                    }
                }
            }

            mEvents.clear();

            

            for(auto &newEvent : StillPressed)
            {
                mEvents.emplace_back(InputEvent{kStillPressed, static_cast<eInputCode>((newEvent & 0xFFFF0000) >> 16), 0});
            }

            for(auto &newEvent : newPressed)
            {
                
                mEvents.emplace_back(InputEvent{kPressed, static_cast<eInputCode>((newEvent & 0xFFFF0000) >> 16), 0});
            }

            for(auto &newEvent : newReleased)
            {
                
                mEvents.emplace_back(InputEvent{kReleased, newEvent.code, 0});
            }
        }

        /**
         * TODO: Has to be changed by a reinterpreting system
        */
        void parseInputRawData(const std::vector<uint8_t> &data)
        {
            std::vector<uint32_t> data32b;

            for(int i = 0; i < data.size() / 4; i++)
            {
                data32b.emplace_back(readUInt32ValueFromByteVector(data.cbegin() + i * 4));
            }

            // TODO: add last incomplete bytes (normally not)
            parseInputData(data32b);

        }

        const std::vector<InputEvent> &getEvents() const
        {
            return mEvents;
        }

        void print() const
        {
            if(mEvents.size() <= 0) return;
            
            std::cout << "Events:\n";
            for(auto &event : mEvents)
            {
                std::cout << " -" << event.status << " " << event.code << event.value << "\n";
            }
        }

    };

    
} // namespace Iliade::Inputs

