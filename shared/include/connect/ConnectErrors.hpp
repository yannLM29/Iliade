/**
 * @file IliadeErrors.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

namespace Iliade::Connect
{
    
    enum errors : int 
    {
        kNoError = 0,
        kTimeOut = 1, // offset
        kBadDescriptor,
        kConnectRefused,
        kConnectReset,
        kMemoryFault,
        kInterrupted,
        kInvalidArg,
        kNoMem,
        kNotConnected,
        kNotSocket,
        kNoWriteAccess,
        kDesAddrReq,
        kAlreadyConnected,
        kMsgSize,
        kNoBufs,
        kNotSuppFlag,
        kUnixPipe
    };
    
} // namespace Iliade
