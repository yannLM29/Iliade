/**
 * @file PlayableElement.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "physics/GameElement.hpp"
#include "inputs/ReceivedInputManager.hpp"

namespace Iliade
{
    class PlayableElement : public Iliade::Physics::GameElement
    {
    private:
        
    public:
        PlayableElement(GameScene &scene, bool isPStatic = false) : Iliade::Physics::GameElement(scene, isPStatic)
        {

        }

        PlayableElement(GameComponent *parentComponent, bool isPrivate = false, bool isPStatic = false) : Iliade::Physics::GameElement(parentComponent, isPrivate, isPStatic)
        {

        }

        int getType() override
        {
            return eComponentType::kPlayableElement;
        }

        template<typename lambda>
        std::vector<int> getVisibleComponentsList(lambda&& func) const
        {
            auto lamb = [&](auto comp)
            {
                if((comp->getConstParentComponent() == this || !comp->isPrivate()) && !comp->isStatic())
                {
                    return func(comp);
                }

                return false;
            };

            return std::move(getConstParentScene()->getVisibleComponentsList(lamb));
        }


        virtual void interact(const Iliade::Inputs::ReceivedInputManager &inputManager, int deltaT) = 0;

    };
    
    
    
} // namespace Iliade::
