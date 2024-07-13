/**
 * @file SfmlSpriteRessource.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "graphics/ISpriteRessource.hpp"

namespace Iliade::Graphics::Sfml
{
    class SfmlIliadeGraphics;
    
    class SfmlSpriteRessource : public Iliade::Graphics::ISpriteRessource
    {
    private:
        sf::Sprite mSprite;
        int mTextureId;

    public:
        SfmlSpriteRessource(SfmlIliadeGraphics &graphicEngine, std::string texturePath);
        ~SfmlSpriteRessource();

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline sf::Sprite &getSfSprite() noexcept
        {
            return mSprite;
        }

        inline float getPositionX() const noexcept
        {
            return mSprite.getPosition().x;
        }

        inline float getPositionY() const noexcept
        {
            return mSprite.getPosition().y;
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline void setPosition(float x, float y)
        {
            mSprite.setPosition(x, y);
        }

        void setRotation(float deg)
        {
            mSprite.setRotation(deg);
        }
        
        void setFrame(Frame &frame) override;
        void setScale(float scale) override;
        void changeResolution(int w, int h) override;
        void setSmooth(bool smooth) override;
        void setColor(int r, int g, int b, int alpha) override;

        

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SHOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    };
    
    
} // namespace Iliade::Graphics::Sfml
