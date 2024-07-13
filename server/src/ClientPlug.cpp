/**
 * @file ClientPlug.cpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ClientPlug.hpp"
#include "Server.hpp"
#include "core/PlayableElement.hpp"

namespace Iliade::Connect
{
    ClientPlug::ClientPlug(Server &serverRef, Iliade::IliadeEngine &engine, SOCKET sock, uint16_t udpInputPort, uint16_t udpOutputPort, PlayableElement *controledPlayer) : 
        Plug(engine, sock),
        mServerRef(serverRef),
        mUdpPlug(getConnectedIpAddrRaw(), udpInputPort, udpOutputPort, serverRef),
        mControledPlayerPtr(controledPlayer),
        mMainThread([this](){this->update();})
    {

    }

    ClientPlug::~ClientPlug()
    {
        mMainThreadRunning = false;
        if(mMainThread.joinable())
        {
            mMainThread.join();
        }
    }

    void ClientPlug::onDisconnect()
    {
        mServerRef.removeClient(mInfos.mSessionId);
    }
} // namespace Iliade::Connect
