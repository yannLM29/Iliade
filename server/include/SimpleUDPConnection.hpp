/**
 * @file SimpleUDPConnection.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <memory>

#include "connect/IConnection.hpp"
#include "connect/UnixErrors.hpp"

namespace Iliade::Connect
{
    class Server;
    class SimpleUDPConnection : public Iliade::Connect::IConnection
    {
    private:
        Server &mServerRef;
        SOCKADDR_IN mClientAddrToSend = { 0 };
        SOCKADDR_IN mClientAddrToRecv = { 0 };

        // std::queue<std::vector<uint8_t>> mMessagesInQueue;
        std::vector<uint8_t> mReceivedMessage;
        std::mutex mReceivedMessageMutex;

        bool mValid = true;
    public:
        SimpleUDPConnection(uint32_t clientAddress, uint16_t inputPort, uint16_t outputPort, Server &serverRef) : mServerRef(serverRef)
        {
            mClientAddrToSend.sin_addr.s_addr = clientAddress;
            mClientAddrToSend.sin_family = AF_INET;
            mClientAddrToSend.sin_port = htons(outputPort);

            mClientAddrToRecv.sin_addr.s_addr = clientAddress;
            mClientAddrToRecv.sin_family = AF_INET;
            mClientAddrToRecv.sin_port = htons(inputPort);

        }

        ~SimpleUDPConnection()
        {

        }

        int syncSend(const std::vector<uint8_t> &data, errors& outError);
        
        std::vector<uint8_t> syncRecv(int size, errors& outError)
        {
            std::vector<uint8_t> dataIn = {};
            outError = kNoError;

            mReceivedMessageMutex.lock();
            // if(!mMessagesInQueue.empty())
            // {
            //     dataIn = mMessagesInQueue.front();
            //     mMessagesInQueue.pop();
            // }
            dataIn = mReceivedMessage;
            mReceivedMessageMutex.unlock();

            return std::move(dataIn);
        }

        void addRecvdMessage(const std::vector<uint8_t> &data)
        {
            mReceivedMessageMutex.lock();
            // mMessagesInQueue.emplace(data);
            mReceivedMessage = data;
            mReceivedMessageMutex.unlock();
        }

        bool asyncSend(const std::vector<uint8_t> &data, const std::function<void(int, errors)>& onSended)
        {

        }

        bool asyncRecv(int size, const std::function<void(const std::vector<uint8_t>&, errors)>& onRecv)
        {

        }

        bool setSendTimeout(int ms)
        {
        }

        bool setRecvTimeout(int ms)
        {
        }

        std::string getConnectedIpAddr() const
        {
            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(mClientAddrToSend.sin_addr), ip_str, sizeof(ip_str));
            
            return std::string(ip_str);
        }

        uint32_t getConnectedIpAddrRaw() const
        {
            return mClientAddrToRecv.sin_addr.s_addr;
        }

        uint16_t getConnectedPort() const
        {
            return mClientAddrToSend.sin_port;
        }

        uint16_t getLocalPort() const
        {
            return ntohs(mClientAddrToRecv.sin_port);
        }


        bool isValid() const noexcept
        {
            return mValid;
        }

    };

}

