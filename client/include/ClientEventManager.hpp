/**
 * @file ClientEventManager.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-07-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "connect/Events/EventManager.hpp"
#include "core/GameScene.hpp"
#include "connect/Events/AnimationEvents.hpp"
#include "graphics/SpriteAsset.hpp"

namespace Iliade::Connect
{
    class ClientEventManager : public EventManager
    {
    private:
        GameScene *mScenePtr;
    public:
        ClientEventManager(GameScene *targetScene) : mScenePtr(targetScene)
        {

        }

        void sendEvent(std::unique_ptr<Event> event, int targetId = 0)
        {
            
        }

        void treatAnimStart(std::unique_ptr<Event> event)
        {
            Events::StartAnimEvent* anim = reinterpret_cast<Events::StartAnimEvent*>(event.get());
            auto elem = mScenePtr->getComponentById(anim->getId());

            if(elem && elem->getType() == kSpriteAsset && anim->getType() == kStartAnim)
            {
                auto sprite = reinterpret_cast<Iliade::Graphics::SpriteAsset*>(elem);
                sprite->localStartAnimation(anim->getAnimationIndex(), anim->getSpeed(), 
                                            anim->getIsOneShot(), anim->getCutLast());
            }
        }

        void treatAnimSpeed(std::unique_ptr<Event> event)
        {

        }

        void treatAnimStop(std::unique_ptr<Event> event)
        {
            Events::StopAnimEvent* anim = reinterpret_cast<Events::StopAnimEvent*>(event.get());
            auto elem = mScenePtr->getComponentById(anim->getId());

            if(elem && elem->getType() == kSpriteAsset && anim->getType() == kStopAnim)
            {
                auto sprite = reinterpret_cast<Iliade::Graphics::SpriteAsset*>(elem);
                sprite->localStopAnimation();
            }
        }

        void treatChatMessage(std::unique_ptr<Event> event)
        {

        }
    };

       
} // namespace Iliade::Connect
