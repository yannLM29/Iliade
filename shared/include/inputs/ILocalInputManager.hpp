/**
 * @file IInputManager.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <vector>
#include <cstdint>

#include "inputs/InputEvent.hpp"


namespace Iliade::Inputs
{
    class ILocalInputManager
    {
    public:
        virtual bool getWindowOpenedState() = 0;
        virtual const std::vector<InputEvent> &getInputEvents() = 0;
        virtual const std::vector<uint32_t> &getInputData() = 0;
        virtual std::vector<uint8_t> getRawInputData() = 0;
    };


    
} // namespace Iliade::Inputs




