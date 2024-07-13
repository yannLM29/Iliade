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

        // Send
        void sendEvent(std::unique_ptr<Event> event, int targetId = 0) override;

        // Recv
        void treatAnimStart(std::unique_ptr<Event> event) override;
        void treatAnimSpeed(std::unique_ptr<Event> event) override;
        void treatAnimStop(std::unique_ptr<Event> event) override;
        void treatChatMessage(std::unique_ptr<Event> event) override;

        
        
    };

} // namespace Iliade::Connect

