/**
 * @file ServerPlug.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "connect/Plug.hpp"
#include "SimpleUDPConnection.hpp"
namespace Iliade::Connect
{
    class ServerPlug : public Plug
    {
    private:
        SimpleUDPConnection mUdpPlug;
    public:
        ServerPlug(Iliade::IliadeEngine &engine, std::string serverAdress, int tcpPort, uint16_t udpInputPort, uint16_t udpOutputPort)
            : Plug(engine, serverAdress, tcpPort),
              mUdpPlug(serverAdress, udpInputPort, udpOutputPort)
        {

        }

        ~ServerPlug()
        {

        }

        int sendUdp(const std::vector<uint8_t> &data, errors& outError)
        {
            return mUdpPlug.syncSend(data, outError);
        }

        std::vector<uint8_t> recvUdp(int size, Iliade::Connect::errors &outError)
        {
            return mUdpPlug.syncRecv(size, outError);
        }
    };
    
    
}