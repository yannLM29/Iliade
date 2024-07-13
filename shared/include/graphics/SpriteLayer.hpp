/**
 * @file SpriteLayer.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <memory>
#include <iostream>

#include "graphics/Frame.hpp"
#include "graphics/Animation.hpp"
#include "graphics/ISpriteRessource.hpp"

namespace Iliade::Graphics
{
    class ISpriteRessource;
    class IliadeGraphics;

    class SpriteLayer
    {
        int mSelectedAnimation;
        int mCurrentFrameIndex;
        std::vector<Animation> mAnimations;

        std::unique_ptr<ISpriteRessource> mSpriteImplem;
        
    public:
        SpriteLayer(std::unique_ptr<ISpriteRessource> sprite, std::vector<Animation> animations) : mAnimations(std::move(animations)), mSpriteImplem(std::move(sprite))
        {
            mSelectedAnimation = 0;
            mCurrentFrameIndex = 0;
            
            setFrame(0, 0);
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline ISpriteRessource &getSpriteImplem() noexcept
        {
            return *mSpriteImplem;
        }

        /**
         * @brief Get the Animation list of this
         * 
         * @return std::vector<Animation>& 
         */
        inline std::vector<Animation> &getAnimation() noexcept
        {
            return mAnimations;
        }

        /**
         * @brief Get the Sprite Impl Ref object
         * @warning Can be nullptr
         * @return mSpriteImplem& 
         */
        inline std::unique_ptr<ISpriteRessource> &getSpriteImplRef() noexcept
        {
            return mSpriteImplem;
        }

        inline bool isLastFrameOfAnim() const noexcept
        {
            return mAnimations[mSelectedAnimation].frames.size() == mCurrentFrameIndex + 1;
        }

        inline float getPositionX() const noexcept
        {
            return mSpriteImplem->getPositionX();
        }

        inline float getPositionY() const noexcept
        {
            return mSpriteImplem->getPositionY();
        }



        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        inline void setPosition(float x, float y)
        {
            mSpriteImplem->setPosition(x, y);
        }

        inline void setRotation(float deg)
        {
            mSpriteImplem->setRotation(deg);
        }

        inline void setScale(float scale)
        {
            mSpriteImplem->setScale(scale);
        }

        inline void setSmooth(bool smooth)
        {
            mSpriteImplem->setSmooth(smooth);
        }

        inline void setColor(int r = 255, int g = 255, int b = 255, int alpha = 255)
        {
            mSpriteImplem->setColor(r, g, b, alpha);
        }

        /**
         * @brief Choose the current animation
         * 
         * @param animationIndex 
         */
        inline void chooseAnimation(int animationIndex)
        {
            if(animationIndex >= mAnimations.size())
            {
                throw std::logic_error("Animation index is bigger than animation list");
            }

            mSelectedAnimation = animationIndex;
        }


        /**
         * @brief Set the Frame object and set sprite implementation with it
         * 
         * @param currentFrame 
         * @param animationIndex 
         */
        void setFrame(int currentFrame, int animationIndex = -1);




        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RUNTIME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        /**
         * @brief Update the animation by passing to next frame
         * 
         */
        void updateAnimation();


        /**
         * @brief Set the animation frame of the current animation to 0
         * 
         */
        inline void resetAnimation()
        {
            setFrame(0);
        }


        /**
         * @brief Call the graphic engine to display itself, it will display with the displayedFrame
         * 
         * @param graphicEngine 
         */
        void display(IliadeGraphics &graphicEngine);

        
    };
    
} // namespace Iliade::Graphics
