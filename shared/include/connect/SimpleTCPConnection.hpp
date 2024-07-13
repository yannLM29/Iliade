/**
 * @file SimpleTCPConnection.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <sys/socket.h>
#include <thread>
#include <semaphore>
#include <iostream>
#include <tuple>
#include <queue>
#include <atomic>
#include <functional>

#include "connect/IConnection.hpp"
#include "connect/UnixErrors.hpp"

namespace Iliade::Connect
{
    class SimpleTCPConnection : public IConnection
    {
    private:
        SOCKET mSocket;

        std::binary_semaphore mSemRecv;
        std::binary_semaphore mSemRecvOut;
        std::thread mThreadRecv;
        std::function<void(const std::vector<uint8_t>&, errors)> mRecvCallback;
        int mRecvSize;
        std::atomic_bool mThreadRecvRunning = true;

        std::binary_semaphore mSemSend;
        std::queue<std::tuple<std::vector<uint8_t>,std::function<void(int, errors)>>> mAsyncSendQueue;
        std::mutex mAsyncSendQueueMutex;
        std::thread mThreadSend;
        std::atomic_bool mThreadSendRunning = true;
        
        std::atomic_bool mValid = false;

    public:
        SimpleTCPConnection(SOCKET sock) :
            mSocket(sock),
            mSemRecv(0),
            mSemRecvOut(1),
            mThreadRecv([this](){this->threadRecvRoutine();}),
            mSemSend(0),
            mThreadSend([this](){this->threadSendRoutine();})
        {
            mValid = true;
        }

        SimpleTCPConnection(std::string address, int port) :
            mSemRecv(0),
            mSemRecvOut(1),
            mThreadRecv([this](){this->threadRecvRoutine();}),
            mSemSend(0),
            mThreadSend([this](){this->threadSendRoutine();})
        {
            mSocket = socket(AF_INET, SOCK_STREAM, 0);
            if(mSocket == INVALID_SOCKET)
            {
                throw std::runtime_error("Couldn't create socket");
            }

            SOCKADDR_IN sin = { 0, 0, 0, 0 };

            sin.sin_addr.s_addr = inet_addr(address.c_str());
            sin.sin_port = htons(port);
            sin.sin_family = AF_INET;

            if(connect(mSocket,reinterpret_cast<SOCKADDR *>(&sin), sizeof(SOCKADDR)) == SOCKET_ERROR)
            {
                throw std::runtime_error("Couldn't connect");
            }

            mValid = true;
        }
        
        ~SimpleTCPConnection() 
        {
            close(mSocket);

            mThreadRecvRunning = false;
            mThreadSendRunning = false;

            mSemRecv.release();
            mSemSend.release();
        
            if(mThreadRecv.joinable()) 
            {
                mThreadRecv.join();
            }
            
            if(mThreadSend.joinable())
            {
                mThreadSend.join();
            }     
        }

        int syncSend(const std::vector<uint8_t> &data, errors& outError)
        {
            if(mSocket <= 0 || !isValid()) return 0;
            int n = send(mSocket, data.data(), data.size(), 0);
            outError = kNoError;
            if(n < 0)
            {
                outError = analyseFromSend();
            }

            return n;
        }

        std::vector<uint8_t> syncRecv(int size, errors& outError)
        {
            std::vector<uint8_t> dataIn;
            dataIn.resize(size);

            int n = recv(mSocket, dataIn.data(), size, 0);
            outError = kNoError;
            if(n == 0)
            {
                mValid = false;
                dataIn.resize(0);
            }
            else if(n < 0)
            {
                outError = analyseFromRecv();
                if(outError == kConnectReset)
                {
                    mValid = false;
                }
                dataIn.resize(0);
            }
            else
            {
                dataIn.resize(n);
            }

            return dataIn;

        }

        bool asyncSend(const std::vector<uint8_t> &data, const std::function<void(int, errors)>& onSended)
        {
            if(mSocket == 0 || !isValid()) return false;
            mAsyncSendQueueMutex.lock();
                mAsyncSendQueue.emplace(std::make_tuple(data, onSended));
            mAsyncSendQueueMutex.unlock();

            mSemSend.release();

            return true;
        }

        bool asyncRecv(int size, const std::function<void(const std::vector<uint8_t>&, errors)>& onRecv)
        {
            if(mSocket == 0 || !isValid()) return false;
            mSemRecvOut.acquire();
            mRecvSize = size;
            mRecvCallback = onRecv;
            mSemRecv.release();

            return true;
        }

        bool setSendTimeout(int ms)
        {
            struct timeval timeout;      
            timeout.tv_sec = ms / 1000;
            timeout.tv_usec = (ms % 1000) * 1000;

            if (setsockopt (mSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
            {
                return false;
            }
            return true;
        }

        bool setRecvTimeout(int ms)
        {
            struct timeval timeout;      
            timeout.tv_sec = ms / 1000;
            timeout.tv_usec = (ms % 1000) * 1000;

            if (setsockopt (mSocket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0)
            {
                return false;
            }
            return true;
        }

        std::string getConnectedIpAddr() const
        {
            SOCKADDR_IN remote_addr;
            socklen_t addr_len = sizeof(SOCKADDR_IN);

            if (getpeername(mSocket, (SOCKADDR*)&remote_addr, &addr_len) == -1) {
                return "";
            }
            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(remote_addr.sin_addr), ip_str, sizeof(ip_str));
            
            return std::string(ip_str);
        }

        uint32_t getConnectedIpAddrRaw() const
        {
            struct sockaddr_in remote_addr;
            socklen_t addr_len = sizeof(struct sockaddr_in);

            if (getpeername(mSocket, (SOCKADDR*)&remote_addr, &addr_len) == -1) {
                return 0;
            }

            return remote_addr.sin_addr.s_addr;
        }

        uint16_t getConnectedPort() const
        {
            struct sockaddr_in remote_addr;
            socklen_t addr_len = sizeof(struct sockaddr_in);

            if (getpeername(mSocket, (SOCKADDR*)&remote_addr, &addr_len) == -1) {
                return 0;
            }

            return ntohs(remote_addr.sin_port);
        }

        uint16_t getLocalPort() const
        {
            struct sockaddr_in local_addr;
            socklen_t addr_len = sizeof(struct sockaddr_in);

            if(getsockname(mSocket, (SOCKADDR*)&local_addr, &addr_len))
            {
                return 0;
            }
            
            return ntohs(local_addr.sin_port);
        }

        bool isValid() const noexcept
        {
            return mValid;
        }

    private:
        void threadRecvRoutine() 
        {
            while (mThreadRecvRunning)
            {
                mSemRecv.acquire();
                if(!mThreadRecvRunning)
                {
                    return;
                }

                errors error = kNoError;
                std::vector<uint8_t> dataIn = syncRecv(mRecvSize, error);

                mSemRecvOut.release();
                mRecvCallback(dataIn, error);
                
            }
        }

        void threadSendRoutine()
        {
            while (mThreadSendRunning)
            {
                mSemSend.acquire();
                if(!mThreadSendRunning)
                {
                    return;
                }

                mAsyncSendQueueMutex.lock();
                    if(mAsyncSendQueue.empty())
                    {
                        mAsyncSendQueueMutex.unlock();
                        continue;
                        
                    }

                    auto sendingData = mAsyncSendQueue.front();
                    mAsyncSendQueue.pop();

                mAsyncSendQueueMutex.unlock();

                auto dataToSend = std::get<0>(sendingData);
                auto callback = std::get<1>(sendingData);

                errors error = kNoError;
                int n = syncSend(dataToSend, error);
                callback(n, error);
            }
        } 
    };

} // namespace Iliade::Connect

