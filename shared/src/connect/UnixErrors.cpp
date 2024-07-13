/**
 * @file UnixErrors.cpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "connect/UnixErrors.hpp"

namespace Iliade::Connect
{
    errors analyseFromRecv()
    {
        switch (errno)
        {
            case EAGAIN:
                return kTimeOut;
            case EBADF:
                return kBadDescriptor;
            case ECONNREFUSED:
                return kConnectRefused;
            case EFAULT:
                return kMemoryFault;
            case EINTR:
                return kInterrupted;
            case EINVAL:
                return kInvalidArg;
            case ENOMEM:
                return kNoMem;
            case ENOTCONN:
                return kNotConnected;
            case ENOTSOCK:
                return kNotSocket;
            default:
                return kNoError;
        }

        return kNoError;
    }

    errors analyseFromSend()
    {
        switch (errno)
        {
            case EACCES:
                return kNoWriteAccess;
            case EAGAIN:
                return kTimeOut;
            case EBADF:
                return kBadDescriptor;
            case ECONNRESET:
                return kConnectReset;
            case EDESTADDRREQ:
                return kDesAddrReq;
            case EFAULT:
                return kMemoryFault;
            case EINTR:
                return kInterrupted;
            case EINVAL:
                return kInvalidArg;
            case EISCONN:
                return kAlreadyConnected;
            case EMSGSIZE:
                return kMsgSize;
            case ENOBUFS:
                return kNoBufs;
            case ENOMEM:
                return kNoMem;
            case ENOTCONN:
                return kNotConnected;
            case ENOTSOCK:
                return kNotSocket;
            case EOPNOTSUPP:
                return kNotSuppFlag;
            case EPIPE:
                return kUnixPipe;
            default:
                return kNoError;
        }
    }
}