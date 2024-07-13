/**
 * @file EventManager.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-07-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <array>
#include <tuple>
#include <functional>

#include "connect/Events/Event.hpp"

namespace Iliade::Connect
{
    class EventManager
    {
    private:
        std::array<std::tuple<eEventTypes, std::function<void(std::unique_ptr<Event>)>>, 4> mLookUpTable = 
        {{
            {kStartAnim,        [this](std::unique_ptr<Event> e){this->treatAnimStart(std::move(e));}},
            {kChangeAnimSpeed,  [this](std::unique_ptr<Event> e){this->treatAnimSpeed(std::move(e));}},
            {kStopAnim,         [this](std::unique_ptr<Event> e){this->treatAnimStop(std::move(e));}},
            {kChatMessage,      [this](std::unique_ptr<Event> e){this->treatChatMessage(std::move(e));}}
        }};

    public:
        void treatEvent(std::unique_ptr<Event> event)
        {
            for(auto &event_tuple : mLookUpTable)
            {
                if(std::get<0>(event_tuple) == event->getType())
                {
                    std::get<1>(event_tuple)(std::move(event));
                    return;
                }
            }
        }

        virtual void sendEvent(std::unique_ptr<Event> event, int targetId = 0) = 0;

        virtual void treatAnimStart(std::unique_ptr<Event> event) = 0;
        virtual void treatAnimSpeed(std::unique_ptr<Event> event) = 0;
        virtual void treatAnimStop(std::unique_ptr<Event> event) = 0;
        virtual void treatChatMessage(std::unique_ptr<Event> event) = 0;
    };
    
    
} // namespace Iliade::Connect
