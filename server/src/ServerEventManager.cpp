#include "ServerEventManager.hpp"
#include "Server.hpp"

#include "connect/Events/ChatEvents.hpp"

namespace Iliade::Connect
{
    ServerEventManager::ServerEventManager(Server &serverRef) : mServerRef(serverRef)
    {
        
    }

    void ServerEventManager::treatAnimStart(std::unique_ptr<Event> event) {}

    void ServerEventManager::treatAnimSpeed(std::unique_ptr<Event> event) {}

    void ServerEventManager::treatAnimStop(std::unique_ptr<Event> event) {}

    void ServerEventManager::treatChatMessage(std::unique_ptr<Event> event)
    {
        // Events::ChatEvent *chatEventPtr = reinterpret_cast<Events::ChatEvent*>(event.get());
        // event.release();
        // auto chatEvent = std::make_unique<Events::ChatEvent>(chatEventPtr);
    }

} // namespace Iliade::Connect
