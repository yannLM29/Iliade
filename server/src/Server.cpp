/**
 * @file Server.cpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Server.hpp"
#include "ClientPlug.hpp"

namespace Iliade::Connect
{
    void Server::acceptRoutine()
    {
        mAcceptStart.acquire();

        while(mAcceptRunning)
        {
            SOCKADDR_IN clientSin = { 0 };
            SOCKET clientSocket;

            int sinsize = sizeof(clientSin);

            clientSocket = accept(mSocket, (SOCKADDR *)&clientSin, (socklen_t*)(&sinsize));

            if(clientSocket == INVALID_SOCKET)
            {
                std::cout << strerror(errno) << "\n";
                mEngineRef.errorLog("Error during client accept");
                break;
            }
            auto scenes = mEngineRef.getScenes();
            if(scenes.size() == 0)
            {
                mEngineRef.errorLog("no scene!");
            }
            auto linked_playable_element = mCallbacks.onConnectPlayerAssignment();
            
            mClientLock.begin_write();
                auto &newClient = mClients.emplace_back(std::make_unique<ClientPlug>(*this, mEngineRef, clientSocket, mUdpInputPort, sUdpOutPort++, linked_playable_element));
            mClientLock.end_write();

            mEngineRef.log("New Client: " + newClient->getConnectedIpAddr() + " with udp port: " + std::to_string((int)ntohs(newClient->getUdpPlug().getConnectedPort())));
        }
    }

    void Server::removeClient(int sessionId)
    {
        mClientsToRemoveMutex.lock();
        mClientsToRemove.emplace(sessionId);
        mClientsToRemoveMutex.unlock();
    }

    void Server::removeClientUpdate()
    {
        mClientLock.begin_write();
        mClientsToRemoveMutex.lock();
        while(!mClientsToRemove.empty())
        {
            int id = mClientsToRemove.front();
            mClientsToRemove.pop();

            mClientsToRemoveMutex.unlock();
            mClients.remove_if([&](const std::unique_ptr<ClientPlug> &client){
                if(client->getInfo().mSessionId == id)
                {
                    mEngineRef.log("Client " + std::to_string(client->getInfo().mSessionId) + " disconnected");
                    return true;
                }
                return false;
            });
            mClientsToRemoveMutex.lock();
        }
        mClientsToRemoveMutex.unlock();
        mClientLock.end_write();

    }

    void Server::update(int ms)
    {
        removeClientUpdate();
    }

    void Server::udpReaderRoutine()
    {
        mUdpReaderStart.acquire();
        while (mUdpReaderRunning)
        {
            int size = 100;
            std::vector<uint8_t> data;
            data.resize(size);

            SOCKADDR_IN remoteAddr;
            socklen_t remoteAddrLength = sizeof(remoteAddr);

            int n = recvfrom(mUdpSocket, data.data(), size, 0, (SOCKADDR *)&remoteAddr, &remoteAddrLength);

            if(n <= 0)
            {
                std::cout << "error ";
                std::cout << analyseFromRecv() << "\n";
               continue;
            }

            data.resize(n);

            auto clientToRecv = std::find_if(mClients.begin(), mClients.end(), [&](std::unique_ptr<ClientPlug> &client) {
                std::cout << client->getUdpPlug().getConnectedPort() << "  " << remoteAddr.sin_port << "\n";
                return client->getConnectedIpAddrRaw() == remoteAddr.sin_addr.s_addr && client->getUdpPlug().getConnectedPort() == remoteAddr.sin_port;
            });

            if(clientToRecv != mClients.end())
            {
                (*clientToRecv)->getUdpPlug().addRecvdMessage(data);
            }     
        }
    }

    int Server::sendUdpMessage(SOCKADDR_IN clientAddrToSend, const std::vector<uint8_t> &data, errors &outError)
    {
        mUdpSendMutex.lock();
        int n = sendto(mUdpSocket, data.data(), data.size(), 0, (SOCKADDR *)&clientAddrToSend, sizeof(clientAddrToSend));
        mUdpSendMutex.unlock();

        std::cout << "sended UDP message of " << n <<" bytes to " << ntohs(clientAddrToSend.sin_port) << " / " << clientAddrToSend.sin_port << "\n";
        return n;
    }

    void Server::treatEvent(std::unique_ptr<Event> event)
    {
        mEventManager.treatEvent(std::move(event));
    }

} // namespace Iliade::Connect
