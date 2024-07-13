/**
 * @file ClientPlug.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "connect/Plug.hpp"
#include "SimpleUDPConnection.hpp"
#include "PlayerInfo.hpp"
#include "inputs/ReceivedInputManager.hpp"
#include "core/PlayableElement.hpp"

namespace Iliade::Connect
{
    class Server;

    class ClientPlug : public Plug
    {
    private:
        PlayerInfo mInfos;
        Server &mServerRef;
        Iliade::Inputs::ReceivedInputManager mManager;
        SimpleUDPConnection mUdpPlug;
        PlayableElement *mControledPlayerPtr;
        std::thread mMainThread;
        std::atomic_bool mMainThreadRunning = true;

    public:
        ClientPlug(Server &serverRef, Iliade::IliadeEngine &engine, SOCKET sock, uint16_t udpInputPort,
                   uint16_t udpOutputPort, PlayableElement *controledPlayer = nullptr);
        ~ClientPlug();

        void onDisconnect() override;

        inline const PlayerInfo &getInfo() const noexcept
        {
            return mInfos;
        }

        inline SimpleUDPConnection &getUdpPlug()
        {
            return mUdpPlug;
        }

        int sendUdp(const std::vector<uint8_t> &data, errors& outError)
        {
            return mUdpPlug.syncSend(data, outError);
        }

        std::vector<uint8_t> recvUdp(int size, Iliade::Connect::errors &outError)
        {
            return mUdpPlug.syncRecv(size, outError);
        }

        void updatePlayerFromClientData()
        {
            Iliade::Connect::errors error;
            auto data = recvUdp(500, error);

            if(error)
            {
                std::cerr << "error udp recv " << error << "\n";
            }

            
            if(mControledPlayerPtr != nullptr)
            {
                mManager.parseInputRawData(data);
                mControledPlayerPtr->interact(mManager, 20);
            }
        }

        void update() 
        {
            while(mMainThreadRunning)
            {
                updatePlayerFromClientData();

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            
        }
    };
    
} // namespace Iliade::Connect
