/**
 * @file ThisEventManager.hpp
 * @author Yann Le Masson
 * @brief Allows engine to instanciate server event manager without knowing
 * @version 0.1
 * @date 2024-07-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <memory>
#include "ServerEventManager.hpp"

namespace Iliade::Connect
{
    std::unique_ptr<EventManager> CreateEventManager();
} // namespace Iliade::Connect
