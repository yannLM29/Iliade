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

        

        void treatAnimStart(std::unique_ptr<Event> event)
        {
            Events::StartAnimEvent* anim = reinterpret_cast<Events::StartAnimEvent*>(event.get());
            auto elem = mScenePtr->getComponentById(anim->getId());

            if(elem && elem->getType() == anim->getType() /*&& elem->getType() == SpriteAsset*/)
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

        }

        void treatChatMessage(std::unique_ptr<Event> event)
        {

        }
    };

       
} // namespace Iliade::Connect
