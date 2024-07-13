/**
 * @file SpriteAsset.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <vector>
#include <iostream>

#include "core/GameComponent.hpp"
#include "graphics/SpriteLayer.hpp"
#include "graphics/IliadeGraphics.hpp"
#include "core/GameScene.hpp"
#include "connect/Events/AnimationEvents.hpp"

namespace Iliade::Graphics
{

    class SpriteAsset : public Iliade::GameComponent
    {
    private:
        float mScale;

        int mGroundIndex = 0;

        std::vector<SpriteLayer> mLayers;

        bool mIsAnimStarted = false;
        bool mIsOneShotStarted = false;
        float mAnimSpeed = 10;
        float mTimeSinceLastFrame = 0;


    public:
        SpriteAsset(Iliade::GameScene &scene) : Iliade::GameComponent(scene)//, mSprite(dynamic_cast<Sfml::SfmlIliadeGraphics&>(scene.getEngineRef().getGraphicEngineRef()), "./link.png")
        {

        }

        SpriteAsset(Iliade::GameComponent *parentComponent, bool isPrivate = false) : GameComponent(parentComponent, isPrivate)//, mSprite(dynamic_cast<Sfml::SfmlIliadeGraphics&>(parentComponent->getEngineRef().getGraphicEngineRef()), "./link.png")
        {

        }

        ~SpriteAsset()
        {

        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline std::vector<SpriteLayer> &getLayers() noexcept
        {
            return mLayers;
        }

        inline float getAnimSpeed() noexcept
        {
            return mAnimSpeed;
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline void addLayer(SpriteLayer layer)
        {
            mLayers.push_back(std::move(layer));
        }

        inline void setPosition(float x, float y) noexcept override 
        {
            GameComponent::setPosition(x, y);
            for(auto &l : mLayers)
            {
                l.setPosition(getPositionX(), getPositionY());
            }
        }

        inline void setRotation(float angle) noexcept override 
        {
            GameComponent::setRotation(angle);
            for(auto &l : mLayers)
            {
                l.setRotation(angle);
            }
        }

        inline void setScale(float scale)
        {
            for(auto &l : mLayers)
            {
                l.setScale(scale);
            }
        }

        inline void setAnimSpeed(float speed)
        {
            mAnimSpeed = speed;
        }

        inline void setGroundIndex(int index)
        {
            mGroundIndex = index;
        }

        inline void chooseAnimation(int index)
        {
            for(auto &l : mLayers)
            {
                l.chooseAnimation(index);
            }
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SHOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void show(Iliade::Graphics::IliadeGraphics &graphicEngine) override
        {
            graphicEngine.show(this, mGroundIndex);
        }

        void display(Iliade::Graphics::IliadeGraphics &graphicEngine)
        {
            for(auto &layer : mLayers)
            {
                layer.display(graphicEngine);
            }
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ANIMATIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Client side update of animation
         * 
         * @param deltaT 
         */
        void localAnimationUpdate(float deltaT)
        {
            float delay = 1 / (mAnimSpeed / 1000);
            mTimeSinceLastFrame += deltaT;


            if(mTimeSinceLastFrame >= delay)
            {
                mTimeSinceLastFrame = 0;
                if(mIsAnimStarted || mIsOneShotStarted)
                {
                    for(auto &l : mLayers)
                    {
                        if(mIsOneShotStarted && l.isLastFrameOfAnim())
                        {
                            mIsOneShotStarted = false;
                            mIsAnimStarted = false;
                        }
                        l.updateAnimation();
                    }
                }
            }
        }

        /**
         * @brief Client side start of animation
         * 
         * @param animationIndex 
         * @param speed 
         * @param isOneShot 
         * @param cutLast 
         */
        void localStartAnimation(int animationIndex, float speed, bool isOneShot = false, bool cutLast = true)
        {
            mIsOneShotStarted = isOneShot;
            mIsAnimStarted = !isOneShot;
            mAnimSpeed = speed;

            for(auto &l : mLayers)
            {
                l.chooseAnimation(animationIndex);
                l.resetAnimation();
            }
        }

        /**
         * @brief 
         * 
         */
        void localStopAnimation()
        {
            mIsOneShotStarted = false;
            mIsAnimStarted = false;

            for(auto &l : mLayers)
            {
                l.resetAnimation();
            }
        }


        /**
         * @brief Server side start of animation, send animation event to the clients
         * 
         */
        void startAnimation(int animationIndex, float speed, bool isOneShot = false, bool cutLast = true);



        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        virtual void update(int deltaT)
        {
            for(auto &layer : mLayers)
            {
                layer.setPosition(static_cast<float>(getPositionX()), static_cast<float>(getPositionY()));
            }
            
            localAnimationUpdate(deltaT);
        }



        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SERIALISE / DESERIALISE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        std::vector<uint8_t> serialiseData() override
        {
            std::vector<uint8_t> serialised = GameComponent::serialiseData();
            
            addValueToByteVector(mScale, serialised);
            addValueToByteVector(mAnimSpeed, serialised);

            return std::move(serialised);
        }


        int parseData(std::vector<uint8_t> data) override
        {
            parseData(data.begin(), data.end());
        }

        int parseData(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) override
        {
            int offset = GameComponent::parseData(begin, end);

            mScale = readFloatValueFromByteVector(end- 2 * sizeof(float));
            mAnimSpeed = readFloatValueFromByteVector(end- sizeof(float));

            return offset + 2 * sizeof(float);
        }

    };

    
} // namespace Iliade::Grpahics
