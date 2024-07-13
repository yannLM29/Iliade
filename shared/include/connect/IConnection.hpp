/**
 * @file IConnection.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <functional>

#include "connect/CrossSocket.hpp"
#include "connect/ConnectErrors.hpp"

namespace Iliade::Connect
{
    class IConnection
    {

    public:
        virtual int syncSend(const std::vector<uint8_t> &data, errors& outError) = 0;
        virtual std::vector<uint8_t> syncRecv(int size, errors& outError) = 0;

        virtual bool asyncSend(const std::vector<uint8_t> &data, const std::function<void(int, errors)>& onSended) = 0;
        virtual bool asyncRecv(int size, const std::function<void(const std::vector<uint8_t>&, errors)>& onRecv) = 0;

        virtual bool setSendTimeout(int ms) = 0;
        virtual bool setRecvTimeout(int ms) = 0;

        virtual std::string getConnectedIpAddr() const = 0;
        virtual uint32_t getConnectedIpAddrRaw() const = 0;

        virtual uint16_t getConnectedPort() const = 0;
        virtual uint16_t getLocalPort() const = 0;

        virtual bool isValid() const noexcept = 0;

        
    };

    
} // namespace Iliade::Connect
