/**
 * @file Server.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <exception>
#include <thread>
#include <semaphore>
#include <errno.h>
#include <list>
#include <iostream>
#include <string.h>
#include <queue>
#include <mutex>

#include "ServerEventManager.hpp"
#include "core/IliadeEngine.hpp"
#include "connect/CrossSocket.hpp"
#include "connect/UnixErrors.hpp"
#include "ClientPlug.hpp"
#include "IServerCallbacks.hpp"
#include "utils/ReaderWriterLock.hpp"

namespace Iliade::Connect
{
    class ClientPlug;

    class Server
    {
    private:
        SOCKET mSocket;
        IliadeEngine &mEngineRef;

        std::list<std::unique_ptr<ClientPlug>> mClients;
        ReaderWriterLock mClientLock;

        std::thread mAcceptThread;
        std::binary_semaphore mAcceptStart;
        bool mAcceptRunning;

        std::queue<int> mClientsToRemove;
        std::mutex mClientsToRemoveMutex;

        std::thread mUdpReaderThread;
        std::binary_semaphore mUdpReaderStart;
        bool mUdpReaderRunning = true;
        SOCKET mUdpSocket;
        std::mutex mUdpSendMutex;
        IServerCallbacks &mCallbacks;

        int mUdpInputPort = 65450;
        inline static int sUdpOutPort = 44453;

        ServerEventManager mEventManager;

    public:
        Server(IliadeEngine &engine, int port, int connectQueueLength, IServerCallbacks &callbacks)
            : mEngineRef(engine),
              mAcceptThread([this]() {this->acceptRoutine();}),
              mAcceptStart(0),
              mAcceptRunning(true),
              mUdpReaderThread([this]() {this->udpReaderRoutine();}),
              mUdpReaderStart(0),
              mCallbacks(callbacks),
              mEventManager(*this)
        {
            // ---- TCP ----
            mSocket = socket(AF_INET, SOCK_STREAM, 0);
            if(mSocket == INVALID_SOCKET)
            {
                engine.errorLog("Couldn't create TCP server socket");
                throw std::runtime_error("error see iliade logs");
            }

            SOCKADDR_IN sin = { 0 };

            sin.sin_addr.s_addr = htonl(INADDR_ANY);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(port);

            if(bind (mSocket, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR)
            {
                std::cout << strerror(errno) << "\n";
                engine.errorLog("Couldn't bind TCP server socket");
                throw std::runtime_error("error see iliade logs");
            }
            mEngineRef.log("Server TCP socket created");

            if(listen(mSocket, connectQueueLength) == SOCKET_ERROR)
            {
                std::cout << strerror(errno) << "\n";
                engine.errorLog("Server couldn't listen on TCP socket");
                throw std::runtime_error("error see iliade logs");
            }
            mEngineRef.log("Server TCP socket binded");

            // ---- UDP ----
            mUdpSocket = socket(AF_INET, SOCK_DGRAM, 0);
            if(mUdpSocket == INVALID_SOCKET)
            {
                engine.errorLog("Couldn't create UDP server socket");
                throw std::runtime_error("error see iliade logs");
            }

            SOCKADDR_IN sinUdp = { 0 };
            sinUdp.sin_addr.s_addr = htonl(INADDR_ANY);
            sinUdp.sin_family = AF_INET;
            sinUdp.sin_port = htons(mUdpInputPort);

            if(bind (mUdpSocket, (SOCKADDR *) &sinUdp, sizeof(sinUdp)) == SOCKET_ERROR)
            {
                engine.errorLog("Couldn't bind UDP server socket");
                throw std::runtime_error("error see iliade logs");
            }

            mAcceptStart.release();
            mUdpReaderStart.release();
        }
        
        ~Server()
        {
            close(mSocket);
            close(mUdpSocket);

            mAcceptRunning = false;
            mUdpReaderRunning = false;

            if(mAcceptThread.joinable())
            {
                mAcceptThread.join();
            }
            if(mUdpReaderThread.joinable())
            {
                mUdpReaderThread.join();
            }

            mEngineRef.log("Server closed");
        }

        inline std::list<std::unique_ptr<ClientPlug>>& getClientList() noexcept
        {
            return mClients;
        }

        void removeClient(int sessionId);

        void update(int ms);

        int sendUdpMessage(SOCKADDR_IN clientAddrToSend, const std::vector<uint8_t> &data, errors &outError);

        void treatEvent(std::unique_ptr<Event> event);

    private:
        void removeClientUpdate();
        void acceptRoutine();
        void udpReaderRoutine();
    };

    
} // namespace Iliade::Connect
