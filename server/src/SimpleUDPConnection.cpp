/**
 * @file SimpleUDPConnection.cpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "SimpleUDPConnection.hpp"
#include "Server.hpp"
// #include "ClientPlug.hpp"

namespace Iliade::Connect
{
    int SimpleUDPConnection::syncSend(const std::vector<uint8_t> &data, errors& outError)
    {
        return mServerRef.sendUdpMessage(mClientAddrToSend, data, outError);
    }

} // namespace Iliade::Connect
