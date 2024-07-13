/**
 * @file UnixErrors.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include "connect/ConnectErrors.hpp"
#include <errno.h>

namespace Iliade::Connect
{
    errors analyseFromRecv();
    errors analyseFromSend();
}