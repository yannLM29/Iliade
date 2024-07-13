/**
 * @file Plug.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "connect/SimpleTCPConnection.hpp"
#include "core/IliadeEngine.hpp"
#include "connect/Events/Event.hpp"
#include "connect/Events/ChatEvents.hpp"
#include "connect/Events/EventParser.hpp"

namespace Iliade::Connect
{

    class Plug
    {
    private:
        IliadeEngine &mEngineRef;

        SimpleTCPConnection mTcpPlug;

        std::queue<std::unique_ptr<Event>> mEventsIn;
        std::mutex mEventsInMutex;

        int mWaitedEventType;
        int mWaitedEventSize;

    public:
        Plug(Iliade::IliadeEngine &engine, SOCKET sock): 
            mEngineRef(engine),
            mTcpPlug(sock)
        {
            waitForEvent();
        }

        Plug(Iliade::IliadeEngine &engine, std::string tcpAddress, int tcpPort): 
            mEngineRef(engine),
            mTcpPlug(tcpAddress, tcpPort)
        {
            waitForEvent();
        }

        ~Plug()
        {

        }

        bool sendEvent(Event &event)
        {
            auto dataToSend = event.serialise();
            mTcpPlug.asyncSend(dataToSend, [&](int n, Iliade::Connect::errors err){
                std::cout << "Event sended\n";
            });

            return true;
        }

        std::unique_ptr<Event> popEvent()
        {
            std::lock_guard<std::mutex> lock(mEventsInMutex);

            if(mEventsIn.empty())
            {
                return nullptr;
            }

            std::unique_ptr<Event> newEvent = std::move(mEventsIn.front());
            mEventsIn.pop();
            
            return std::move(newEvent);

        }

        // sendGameData();
        // recvGameData();

        inline std::string getConnectedIpAddr() const
        {
            return mTcpPlug.getConnectedIpAddr();
        }

        inline uint32_t getConnectedIpAddrRaw() const
        {
            return mTcpPlug.getConnectedIpAddrRaw();
        }

        

    protected:
        virtual void onDisconnect()
        {

        }

    private:
        void waitForEvent()
        {
            mTcpPlug.asyncRecv(6, [this](const std::vector<uint8_t>& dataIn, errors error) { this->parseEventHeader(dataIn, error); });
        }

        void parseEventHeader(const std::vector<uint8_t> &dataIn, Iliade::Connect::errors error)
        {
            for(auto &d: dataIn)
            {
                std::cout << (int)d << " ";
            }
            std::cout << "\n";

            if(dataIn.size() < 6)
            {
                
                if(dataIn.size() == 0)
                {
                    // mEngineRef.errorLog(error, "In parseEventHeader");
                    onDisconnect();
                    return;
                }
                else
                {
                    mEngineRef.errorLog("dataIn too short in parseEventHeader");
                }

                // waitForEvent();
                return;
            }
            
            mWaitedEventType = static_cast<eEventTypes>(readInt16ValueFromByteVector(dataIn.begin()));
            mWaitedEventSize = readUInt32ValueFromByteVector(dataIn.begin() + 2);

            mTcpPlug.asyncRecv(mWaitedEventSize, [this](const std::vector<uint8_t>& data, errors error) { this->parseEventBody(data, error); }); 
        }

        void parseEventBody(const std::vector<uint8_t>&dataIn, errors error)
        {
            if(dataIn.size() < 6)
            {
                
                if(dataIn.size() == 0)
                {
                    mEngineRef.errorLog(error, "In parseEventBody");
                    onDisconnect();
                    return;
                }
                else
                {
                    mEngineRef.errorLog("dataIn too short in parseEventBody");
                }

                waitForEvent();
            }

            auto newEvent = parseEvent(mWaitedEventType, mWaitedEventSize, dataIn);

            mEventsInMutex.lock();
                mEventsIn.emplace(std::move(newEvent));
            mEventsInMutex.unlock();
            
            waitForEvent();
        }
    };
    
    
} // namespace Iliade::Connect
