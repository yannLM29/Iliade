/**
 * @file GameScene.cpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-04-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <algorithm>
#include <unistd.h>

#include "core/IliadeEngine.hpp"
#include "core/GameScene.hpp"
#include "core/GameComponent.hpp"
#include "physics/IliadePhysics.hpp"


namespace Iliade
{
    GameScene::GameScene(IliadeEngine &engine, float gravityX, float gravityY) : mId(engine.generateNewSceneId()), mEngineRef(engine), mPhysicEngine(gravityX, gravityY)
    {

    }

    GameScene::~GameScene()
    {
        // for(auto &)
    }

    void GameScene::addComponent(GameComponent *newComponent)
    {
        // Check if component is not already in this scene
        auto components_it = std::find_if(mComponents.cbegin(), mComponents.cend(), [&](auto &comp){
            return comp->getId() == newComponent->getId();
        });

        if(components_it != mComponents.cend())
        {
            throw std::logic_error("Try to attach a component who is already in this scene | component_id=" + std::to_string(newComponent->getId()) + " scene_id=" + std::to_string(getId()));
        }

        // Check if component is not already in another scene
        if(newComponent->getParentScene() != nullptr)
        {
            throw std::logic_error("Try to attach a component who is already in a scene | component_id=" + std::to_string(newComponent->getId()) + " scene_id=" + std::to_string(getId()));
        }

        // If it is not a root component it can't be added to the scene
        if(newComponent->getParentComponent() != nullptr)
        {
            throw std::logic_error("Try to attach a component who is not | component_id=" + std::to_string(newComponent->getId()) + " scene_id=" + std::to_string(getId()));
        }
        
        mComponents.emplace_back(newComponent);                    // Add component
        newComponent->_ILIADE_CORE_setParentScene(this);           // Set component parent scene to this

    }

    void GameScene::removeComponent(GameComponent *componentToRemove)
    {
        if(componentToRemove->getParentComponent() != nullptr)
        {
            throw std::logic_error("Try to detach a component who is not a root | component_id=" + std::to_string(componentToRemove->getId()) + " scene_id=" + std::to_string(getId()));
        }

        // Check component parent scene is this
        if(componentToRemove->getParentScene() != this)
        {
            throw std::logic_error("Try to detach a component who's parent is not this | component_id=" + std::to_string(componentToRemove->getId()) + " scene_id=" + std::to_string(getId()));
        }

        int component_list_size = mComponents.size();

        // try to remove component
        auto components_it = mComponents.erase(std::remove_if(mComponents.begin(), mComponents.end(), [&](auto &comp){
            if(comp->getId() == componentToRemove->getId())
            {
                componentToRemove->_ILIADE_CORE_setParentScene(nullptr);
                return true;
            }
            return false;
        }));

        // If no component were removed is because it wasn't part of this
        if(mComponents.size() == component_list_size)
        {
            throw std::logic_error("Try to detach a component which is not on component list of scene | component_id=" + std::to_string(componentToRemove->getId()) + " scene_id=" + std::to_string(getId()));
        }

    }

    GameComponent* GameScene::getComponentById(int id) 
    {
        for(auto &comp : mComponents)
        {
            auto c = comp->getChildById(id);
            if(c) return c;
        }

        return nullptr;
    }

    /**
     * @brief TO IMPLEMENT
     * 
     * @return std::string 
     */
    std::string GameScene::getComponentListDescription()
    {
        std::string st = "";
        // parcourComponents([&](Iliade::GameComponent* c){
        //     st += " - " + c->getId();
        // });

        return st;
    }


    
    GameSceneModel GameScene::copyToModel()
    {
        GameSceneModel model;

        for(auto& comp : mComponents)
        {
            
            if(!comp->isStatic())
            {
                model.mComponents.emplace_back(comp->copyToModel());
            }
        }
        return std::move(model);
    }


    void GameScene::updateFromData(std::vector<uint8_t> data)
    {
        if(data.size() < 4)
        {
            mEngineRef.errorLog("received data size too small to be parsed : " + std::to_string(data.size()));
            return;
        }

        int numberOfComponents = data[0];
            numberOfComponents |= (data[1] << 8);
            numberOfComponents |= (data[2] << 16);
            numberOfComponents |= (data[3] << 24);

        int offset = 4;
        
        int offset_add = 0;

        for(int e = 0; e < numberOfComponents; e++)
        {
            do
            {
                for(int i = 0; i < numberOfComponents; i++)
                {
                    offset_add = mComponents[i]->updateFromData(data.begin() + offset, data.end());

                    if(offset_add >= 0)
                    {
                        break;
                    } 
                }
            }
            while(offset_add < 0);
            
            offset += offset_add;       // verifier offset
        }
        
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RUNTIME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void GameScene::update(int deltaT)
    {
        getPhysicsEngineRef().update(deltaT);

        for(auto &comp : mComponents)
        {
            comp->update(deltaT);
        }
       
    }

    void GameScene::show(Iliade::Graphics::IliadeGraphics &graphicEngine)
    {
        for(auto &comp : mComponents)
        {
            comp->show(graphicEngine);
        }
    }
 

} // namespace Iliade
