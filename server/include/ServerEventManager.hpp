/**
 * @file ServerEventManager.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-07-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "connect/Events/EventManager.hpp"

namespace Iliade::Connect
{
    class Server;

    class ServerEventManager : public EventManager
    {
    private:
        Server &mServerRef;
    public:
        ServerEventManager(Server &serverRef);

        void treatAnimStart(std::unique_ptr<Event> event);
        void treatAnimSpeed(std::unique_ptr<Event> event);
        void treatAnimStop(std::unique_ptr<Event> event);
        void treatChatMessage(std::unique_ptr<Event> event);

        
    };

} // namespace Iliade::Connect

