/**
 * @file DebugRect.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <vector>
namespace Iliade::Graphics
{
    struct DebugRect
    {
        float x;
        float y;
        float w;
        float h;
    };

    struct DebugCircle
    {
        float x;
        float y;
        float r;
    };

    struct PolygonVertice
    {
        float x;
        float y;
    };
    
    struct DebugPolygon
    {
        std::vector<PolygonVertice> vertices;
    };
} // namespace Iliade::Graphics


