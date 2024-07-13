/**
 * @file AttachedStdTypes.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <cstdint>
#include <string>

namespace Iliade
{
    struct AttachedStdInt
    {
        bool mIsPrivate;
        bool mIsStatic;

        int32_t *mValue;
    };

    struct AttachedStdDouble
    {
        bool mIsPrivate;
        bool mIsStatic;

        double *mValue;
    };

    struct AttachedStdString
    {
        bool mIsPrivate;
        bool mIsStatic;

        std::string *mValue;
    };
    
} // namespace Iliade

