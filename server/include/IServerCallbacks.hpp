/**
 * @file IServerCallbacks.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <memory>


namespace Iliade
{
    class PlayableElement;
} // namespace Iliade

namespace Iliade::Connect
{
    class IServerCallbacks
    {
    public:
        virtual bool connectionControl(/**/) = 0;
        virtual PlayableElement* onConnectPlayerAssignment() = 0;
    };


} // namespace Iliade::Connect




