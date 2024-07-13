#include "connect/Events/UnknownEventManager.hpp"
#include "ServerEventManager.hpp"

namespace Iliade::Connect
{
    std::unique_ptr<EventManager> CreateEventManager()
    {
        return std::make_unique<ServerEventManager>();
    }

} // namespace Iliade::Connect
