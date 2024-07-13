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
#include <string>
#include <cstring>
#include <thread>

#include "connect/IConnection.hpp"
#include "connect/UnixErrors.hpp"

namespace Iliade::Connect
{
    class SimpleUDPConnection : public Iliade::Connect::IConnection
    {
    private:
        SOCKET mSocket;

        SOCKADDR_IN mLocalAddr = { 0 };
        SOCKADDR_IN mServerAddr = { 0 };

        std::vector<uint8_t> mReceivedMessage;
        std::mutex mReceivedMessageMutex;
        std::thread mReceiverThread;
        std::atomic_bool mReceiverThreadRunning = true;

        bool mValid = true;
    public:
        SimpleUDPConnection(std::string serverAdress, uint16_t inputPort, uint16_t outputPort) :
            mReceiverThread([this](){this->receveiverThreadRoutine();})
        {
            if ((mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
                throw std::runtime_error("Couldn't bind socket");
            }

            mServerAddr.sin_addr.s_addr = inet_addr(serverAdress.c_str());
            mServerAddr.sin_family = AF_INET;
            mServerAddr.sin_port = htons(outputPort);

            mLocalAddr.sin_addr.s_addr = htonl(INADDR_ANY);
            mLocalAddr.sin_family = AF_INET;
            mLocalAddr.sin_port = htons(inputPort);

            if(bind (mSocket, (SOCKADDR *) &mLocalAddr, sizeof(mLocalAddr)) == SOCKET_ERROR)
            {
                throw std::runtime_error("Couldn't bind udp socket");
            }
            std::cout << "Binded udp on port " << ntohs(mLocalAddr.sin_port) << "\n";

        }

        ~SimpleUDPConnection()
        {
            mReceiverThreadRunning = false;
            if(mReceiverThread.joinable())
            {
                mReceiverThread.join();
            }
        }

        int syncSend(const std::vector<uint8_t> &data, errors& outError)
        {
            int n = sendto(mSocket, data.data(), data.size(), 0, (SOCKADDR*)&mServerAddr, sizeof(mServerAddr));
            return n;
        }
        
        std::vector<uint8_t> syncRecv(int size, errors& outError)
        {
            std::lock_guard<std::mutex> receivedMessageGuardian(mReceivedMessageMutex);
            return mReceivedMessage;
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
            inet_ntop(AF_INET, &(mServerAddr.sin_addr), ip_str, sizeof(ip_str));
            
            return std::string(ip_str);
        }

        uint32_t getConnectedIpAddrRaw() const
        {
            return mServerAddr.sin_addr.s_addr;
        }

        uint16_t getConnectedPort() const
        {
            return ntohs(mServerAddr.sin_port);
        }

        uint16_t getLocalPort() const
        {
            return ntohs(mLocalAddr.sin_port);
        }


        bool isValid() const noexcept
        {
            return mValid;
        }

        private:
        void receveiverThreadRoutine()
        {
            while(mReceiverThreadRunning)
            {
                waitUdpMessage();
                std::this_thread::sleep_for(std::chrono::milliseconds(3));
            }
        }

        void waitUdpMessage()
        {
            std::vector<uint8_t> dataIn = {};
            size_t size = 500;                      // Need to be parameterized
            dataIn.resize(size);
            
            SOCKADDR_IN addrIn;
            socklen_t addrInLen = sizeof(addrIn);
            memset(&addrIn, 0, sizeof(addrIn));

            wait_recv: int n = recvfrom(mSocket, dataIn.data(), (size_t)size, 0, (SOCKADDR*)&addrIn, &addrInLen);

            if(n == 0)
            {
                // end of connection
                std::cout << "server disconnected";
            }
            else if(n < 0)
            {
                auto error = analyseFromRecv();
                throw std::runtime_error("Error recvfrom " + std::to_string((int)error));
            }

            if(addrIn.sin_addr.s_addr != mServerAddr.sin_addr.s_addr)
            {
                char local_ip[INET_ADDRSTRLEN];
                char distant_ip[INET_ADDRSTRLEN];
                
                // Conversion des adresses en chaînes de caractères
                inet_ntop(AF_INET, &(mServerAddr.sin_addr), local_ip, INET_ADDRSTRLEN);
                inet_ntop(AF_INET, &(addrIn.sin_addr), distant_ip, INET_ADDRSTRLEN);

                std::cout << "wrong address " << distant_ip << "is not " << local_ip << "\n";
                goto wait_recv;
            }

            dataIn.resize(n);

            mReceivedMessageMutex.lock();
            mReceivedMessage.resize(n);
            mReceivedMessage = dataIn;
            mReceivedMessageMutex.unlock();
        }


    };

}

