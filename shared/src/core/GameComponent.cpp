/**
 * @file GameComponent.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-04-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "core/IliadeEngine.hpp"
#include "core/GameScene.hpp"
#include "core/GameComponent.hpp"


namespace Iliade
{
    GameComponent::GameComponent(IliadeEngine &engine, GameScene &scene) : mId(engine.generateNewComponentId()), mEngineRef(engine)
    {
        scene.addComponent(this);
    }

    GameComponent::GameComponent(GameScene &scene) : GameComponent(scene.getEngineRef(), scene)
    {
    }

    GameComponent::GameComponent(GameComponent *parentComponent, bool isPrivate) : mId(parentComponent->getEngineRef().generateNewComponentId()), mEngineRef(parentComponent->getEngineRef())
    {
        parentComponent->attachChildComponent(this);
        mIsPrivate = isPrivate;
    }

    GameComponent::~GameComponent()
    {
        if(mParent != nullptr)
        {
            detachFromParent();
        }
        
        detachAllChildren();
    }


    void GameComponent::attachChildComponent(GameComponent *component)
    {   
        // Check component is not null
        if(component == nullptr)
        {
            throw std::invalid_argument("Try to attach nullptr child | parent_id=" + std::to_string(mId));
        }

        // Check that component is an orphan
        if(component->getConstParentComponent() != nullptr)
        {
            throw std::logic_error("Try to attach a child who already has a parent | component_id=" + std::to_string(component->getId()) + "  parent_id=" + std::to_string(mId));
        }

        // Check if the component is an ancesstor of this
        if(isOneOfMyParent(component))
        {
            throw std::logic_error("Try to attach an ancestor as a child | component_id=" + std::to_string(component->getId()) + "  parent_id=" + std::to_string(mId));
        }

        // Check component is not already a child of this
        auto children_it = std::find_if(mChildComponents.cbegin(), mChildComponents.cend(), [&](auto &children) {
            return children->getId() == component->getId();
        });

        if(children_it != mChildComponents.cend())
        {
            throw std::logic_error("Try to attach an already attached child | component_id=" + std::to_string(component->getId()) + "  parent_id=" + std::to_string(mId));
        }

        if(component->getParentScene() != nullptr)                 // If component has a scene throw error
        {
            throw std::logic_error("Try to attach a component to a parent component but it has scene, remove from scene first");
        }


        // Add component to child list and set his parent pointer
        mChildComponents.emplace_back(component);
        component->mParent = this;
    }


    void GameComponent::detachChildComponent(GameComponent *component)
    {
        // Check component is not null
        if(component == nullptr)
        {
            throw std::invalid_argument("Try to detach nullptr child | parent_id=" + std::to_string(mId));
        }
        
        // Check that component is not an orphan
        if(component->getConstParentComponent() == nullptr)
        {
            throw std::logic_error("Try to detach orphan from parent component | component_id=" + std::to_string(component->getId()) + "  parent_id=" + std::to_string(mId));
        }

        // Remove component if it is in list and set his parent pointer at null
        auto beforeSize = mChildComponents.size();
        auto children_it = mChildComponents.erase(std::remove_if(mChildComponents.begin(), mChildComponents.end(), [&](auto &child){
            if(child->getId() == component->getId())
            {
                component->mParent = nullptr;
                return true;
            }
            return false;
        }));

        if(beforeSize == mChildComponents.size())
        {
            throw std::logic_error("Try to detach child who is not known by his parent component | component_id=" + std::to_string(component->getId()) + "  parent_id=" + std::to_string(mId));
        }

    }

    void GameComponent::detachFromParent()
    {
        if(mParent == nullptr)
        {
            throw std::logic_error("Try to detach an orphan | component_id=" + std::to_string(mId));
        }

        mParent->detachChildComponent(this);
    }

    void GameComponent::detachAllChildren()
    {
        for(auto &child : mChildComponents)
        {
            detachChildComponent(child);
        }
    }

    void GameComponent::changeParentComponent(GameComponent *newParentComponent)
    {
        if(mParent == nullptr)
        {
            std::logic_error("Try to change parent component of an orphan | component_id=" + std::to_string(mId) + "  parent_id=" + std::to_string(mParent->getId()));
        }

        mParent->detachChildComponent(this);
        newParentComponent->attachChildComponent(this);
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SCENE ATTACHEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void GameComponent::attachToScene(GameScene &scene)
    {
        scene.addComponent(this);
    }

    void GameComponent::detachFromScene()
    {
        if(mScene == nullptr)
        {
            throw std::logic_error("Try to detach a component that has no scene");
        }

        mScene->removeComponent(this);
    }
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STANDARD TYPE ATTACHEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // void GameComponent::detachStdType(int32_t *data)
    // {
    //     if(data == nullptr)
    //     {
    //         throw std::logic_error("Try to detach a std int which is a nullptr");
    //     }

    //     auto size = mAttachedStdInts.size();
    //     mAttachedStdInts.erase(std::remove_if(mAttachedStdInts.begin(), mAttachedStdInts.end(), [&](auto &attached){
    //         return attached.mValue == data;
    //     })); 
    
    //     if(mAttachedStdInts.size() != size)
    //     {
    //         throw std::logic_error("Try to detach a std int which is not attached to this");
    //     }
    // }

    // void GameComponent::detachStdType(double *data)
    // {
    //     if(data == nullptr)
    //     {
    //         throw std::logic_error("Try to detach a std double which is a nullptr");
    //     }

    //     auto size = mAttachedStdDoubles.size();
    //     mAttachedStdDoubles.erase(std::remove_if(mAttachedStdDoubles.begin(), mAttachedStdDoubles.end(), [&](AttachedStdDouble &attached){
    //         return attached.mValue == data;
    //     })); 
    
    //     if(mAttachedStdDoubles.size() != size)
    //     {
    //         throw std::logic_error("Try to detach a std double which is not attached to this");
    //     }
    // }

    // void GameComponent::detachStdType(std::string *data)
    // {
    //     if(data == nullptr)
    //     {
    //         throw std::logic_error("Try to detach a std string which is a nullptr");
    //     }

    //     auto size = mAttachedStdString.size();
    //     mAttachedStdString.erase(std::remove_if(mAttachedStdString.begin(), mAttachedStdString.end(), [&](auto &attached){
    //         return attached.mValue == data;
    //     })); 
    
    //     if(mAttachedStdString.size() != size)
    //     {
    //         throw std::logic_error("Try to detach a std string which is not attached to this");
    //     }
    // }


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MODEL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    GameComponentModel GameComponent::copyToModel()
    {
        GameComponentModel model = {.mId= getId(),
                                    .mType= getType(),
                                    .mIsPrivate= isPrivate(),
                                    .mIsStatic= isStatic(),
                                    .mData= serialiseData()};

        for(auto &child : mChildComponents)
        {
            if(!child->isStatic())
            {
                model.mChildren.emplace_back(child->copyToModel());
            }
        }

        return std::move(model);
    }
    int GameComponent::updateFromData(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end)
    {
        int offset = 0;

        // Check if input data is at least long enough to store id, type and datasize
        if(end - begin < 12)
        {
            mEngineRef.errorLog("Wrong data size (too small): " + std::to_string(end-begin) + " bytes");
            return -1;
        }

        // Get component id value
        int id = static_cast<int>(*begin) | (static_cast<int>(*(begin+1)) << 8) | (static_cast<int>(*(begin+2)) << 16) | (static_cast<int>(*(begin+3)) << 24);
        if(id != mId)
        {
            return -1;
        }
        
        // Get component data size
        int componentDataSize  = *(begin + 8);
            componentDataSize |= *(begin + 8 + 1) << 8;
            componentDataSize |= *(begin + 8 + 2) << 16;
            componentDataSize |= *(begin + 8 + 3) << 24;

        // Check if total component size is note greater than input data size
        if(begin + 16 + componentDataSize > end)
        {
            mEngineRef.errorLog("Wrong data size (too big):" + std::to_string(16 + componentDataSize) + "greater than " + std::to_string(begin - end) + " bytes");
            return -1;
        }

        // Parse data
        parseData(begin + 12, begin + 12 + componentDataSize);
        
        offset += 12 + componentDataSize;

        // Get number of children components
        int numberOfChildren  = *(begin + offset);
            numberOfChildren |= *(begin + offset + 1) << 8;
            numberOfChildren |= *(begin + offset + 2) << 16;
            numberOfChildren |= *(begin + offset + 3) << 24;

        offset += 4;

        // For each child, updatafromData
        for(int i = 0; i < numberOfChildren; i++)
        {
            // get child id
            int child_id  = *(begin + offset);
                child_id |= *(begin + offset + 1) << 8;
                child_id |= *(begin + offset + 2) << 16;
                child_id |= *(begin + offset + 3) << 24;

            auto selected_child = std::find_if(mChildComponents.begin(), mChildComponents.end(), [&](auto comp){
                return comp->getId() == child_id;
            });

            offset += (*selected_child)->updateFromData(begin+offset , end);
        }


        return offset;
    }

    int GameComponent::parseData(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end)
    {
        if(end-begin < 8)
        {
            mEngineRef.errorLog("data size too short");
            return 0;
        }

        mPositionX = readFloatValueFromByteVector(begin);
        mPositionY = readFloatValueFromByteVector(begin + 4);

        mRotation = readFloatValueFromByteVector(begin + 8);

        return 9;
    }
    
} // namespace Iliade
