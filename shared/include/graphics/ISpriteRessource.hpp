/**
 * @file ISpriteRessource.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "graphics/Frame.hpp"

namespace Iliade::Graphics
{

    class IliadeGraphics;

    class ISpriteRessource
    {
    public:
        // virtual ~ISpriteRessource() = 0;
        
        virtual float getPositionX() const = 0;
        virtual float getPositionY() const = 0;
        virtual void setPosition(float x, float y) = 0;
        virtual void setRotation(float deg) = 0;
        virtual void setFrame(Frame &frame) = 0;
        virtual void setScale(float scale) = 0;
        virtual void changeResolution(int w, int h) = 0;
        virtual void setSmooth(bool smooth) = 0;
        virtual void setColor(int r = 255, int g = 255, int b = 255, int alpha = 255) = 0;
    };
} // namespace Iliade::Graphics::Sfml


