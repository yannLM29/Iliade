#include "connect/Events/UnknownEventManager.hpp"
#include "ClientEventManager.hpp"

namespace Iliade::Connect
{
    std::unique_ptr<EventManager> CreateEventManager()
    {
        return std::make_unique<ClientEventManager>();
    }

} // namespace Iliade::Connect
