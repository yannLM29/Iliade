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

#pragma once

#define UNIQUE_COMPONENT_TYPE_ID __COUNTER__

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cinttypes>

#include "core/ComponentTypeIds.hpp"
#include "core/GameComponentModel.hpp"
#include "core/AttachedStdTypes.hpp"
#include "utils/BitManips.hpp"


namespace Iliade::Graphics
{
    class IliadeGraphics;
} // namespace Iliade::Graphics::IliadeGraphics

namespace Iliade
{
    class IliadeEngine;
    class GameScene;

    /**
     * @brief Basic synchronised game component
     */
    class GameComponent
    {
    private:

        int mId;
        IliadeEngine &mEngineRef;
        GameScene *mScene = nullptr;
        GameComponent *mParent = nullptr;
        bool mIsPrivate = false;
        bool mIsStatic = false;

        std::vector<GameComponent*> mChildComponents;

        std::vector<AttachedStdInt> mAttachedStdInts;
        std::vector<AttachedStdDouble> mAttachedStdDoubles;
        std::vector<AttachedStdString> mAttachedStdString;

        // Data
        float mPositionX = 0, mPositionY = 0;     // --> float
        float mRotation;

        GameComponent(IliadeEngine &engine, GameScene &scene);
        
    public:
        /**
         * @brief Construct a new independent Game Component object
         * 
         * @param scene scene the component is attached to
         */
        GameComponent(GameScene &scene);

        /**
         * @brief Construct a new child Game Component object
         * 
         * @param parentComponent parent component the component is attached to
         */
        GameComponent(GameComponent *parentComponent, bool isPrivate = false);

        ~GameComponent();

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Get the Type of a component object
         * 
         * @return int type id of the component
         */
        virtual int getType()
        {
            return eComponentType::kGameComponent;
        }
        
        /**
         * @brief Get the Id of a component object
         * 
         * @return int 
         */
        inline int getId() const noexcept 
        {
            return mId;
        }

        /**
         * @brief Get the Parent Scene object
         * 
         * @return GameScene* 
         */
        GameScene *getParentScene() noexcept
        {
            if(mScene != nullptr)
            {
                return mScene;
            }

            if(mParent == nullptr)
            {
                return nullptr;
            }

            return mParent->getParentScene();
        }
        
        /**
         * @brief Get the Const Parent Scene object
         * 
         * @return const GameScene*
         */
        const GameScene *getConstParentScene() const noexcept
        {
            if(mScene != nullptr)
            {
                return mScene;
            }

            if(mParent == nullptr)
            {
                return nullptr;
            }

            return mParent->getParentScene();
        }

        /**
         * @brief Get the Parent Component object
         * 
         * @return GameComponent* or nullptr if object don't have parent
         */
        inline GameComponent *getParentComponent() noexcept
        {
            return mParent;
        }

        /**
         * @brief Get the Const Parent Component object
         * 
         * @return const GameComponent* or nullptr if object don't parent
         */
        inline const GameComponent *getConstParentComponent() const noexcept
        {
            return mParent;
        }

        inline std::vector<GameComponent*>& getChildrenComponents() noexcept
        {
            return mChildComponents;
        }

        inline GameComponent* getChildById(int id) noexcept
        {
            if(id == mId)
            {
                return this;
            }

            for(auto &child : mChildComponents)
            {
                GameComponent* c = child->getChildById(id);
                if(c) return c;
            }

            return nullptr;
        }

        inline IliadeEngine& getEngineRef() const noexcept
        {
            return mEngineRef;
        }

        void getComponentBranchDescription(int n, std::string &out)
        {
            for(int i = 0; i < n; i++)
            {
                out += " ";
            }
            out += "| " + std::to_string(getId()) + ": type=" + std::to_string(getType()) + " x=" + std::to_string(getPositionX()) + " y=" + std::to_string(getPositionY()) + "\n";
            for(auto &child : mChildComponents)
            {
                child->getComponentBranchDescription(n+1, out);
            }
        }

        /**
         * @brief Private components data are only send to player that hold this data
         * 
         * @return true 
         * @return false 
         */
        inline bool isPrivate() const noexcept
        {
            return mIsPrivate;
        }

        /**
         * @brief Static components don't change so there not syncronised with client
         * 
         * @return true 
         * @return false 
         */
        inline bool isStatic() const noexcept
        {
            return mIsStatic;
        }

        /**
         * @brief 
         * 
         * @param component component to test
         * @return true component is a ancestor of this
         * @return false component is not a ancestor of this
         */
        bool isOneOfMyParent(GameComponent *component) const
        {
            if(mParent == nullptr)
            {
                return false;
            }
            
            if(mParent == component)
            {
                return true;
            }
            
            return getConstParentComponent()->isOneOfMyParent(component);
        }

        inline float getPositionX() noexcept
        {
            if(getParentComponent() != nullptr)
            {
                return getParentComponent()->getPositionX() + mPositionX;
            }
                
            return mPositionX;
        }

        inline float getPositionY() noexcept
        {
            if(getParentComponent() != nullptr)
            {
                return getParentComponent()->getPositionY() + mPositionY;
            }
            
            return mPositionY;
        } 

        inline int getOffsetX() noexcept
        {
            return mPositionX;
        }

        inline int getOffsetY()
        {
            return mPositionY;
        }

        inline float getRotation() noexcept
        {
            return mRotation;
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        inline void setPrivate(bool state) noexcept
        {
            mIsPrivate = state;
        }

        inline void setStatic(bool state) noexcept
        {
            mIsStatic = state;
        }

        inline virtual void setPosition(float x, float y) noexcept
        {
            mPositionX = x;
            mPositionY = y;
            
        }

        inline virtual void setRotation(float angle)
        {
            mRotation = angle;
        }

        /**
         * @warning Usage of _ILIADE_CORE functions is prohibited
         * 
         * @param new_scene 
         */
        inline void _ILIADE_CORE_setParentScene(GameScene *new_scene)
        {
            mParent = nullptr;
            mScene = new_scene;
        }

        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMPONENT ATTACHEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Attach a child component to this
         * 
         * @param component child to attach, must be free or an exception will be raised
         */
        virtual void attachChildComponent(GameComponent *component);

        /**
         * @brief Detach a child from this
         * 
         * @param component child to detach, must bee attached or an exception will be raised
         */
        virtual void detachChildComponent(GameComponent *component);

        /**
         * @brief Detach all children from this
         * 
         */
        virtual void detachAllChildren();

        /**
         * @brief Detach this from his parent, this must have a parent or an exception will be raised
         * 
         */
        virtual void detachFromParent();

        /**
         * @brief Change the parent of this
         * 
         * @param newParentComponent 
         */
        void changeParentComponent(GameComponent *newParentComponent);


        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SCENE ATTACHEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Attach this component to a scene, can throw an error if component is already attach to a parent or a scene
         * 
         * @param scene 
         */
        void attachToScene(GameScene &scene);

        /**
         * @brief Detach a component from its scene, this will throw an error if components has no parent scene
         * 
         */
        void detachFromScene();


        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STANDARD TYPE ATTACHEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Attach standard type
         * @warning Be careful, if this data is in an allocation like a vector, its adress can change. This will break this attachement !
         * @param data 
         */
        // inline void attachStdType(int32_t *data, bool isPrivate = false, bool isStatic = false)
        // {
        //     if(data == nullptr)
        //     {
        //         throw std::logic_error("Attach a nullptr as a std int");
        //     }
        //     mAttachedStdInts.push_back({isPrivate, isStatic, data});
        // }

        /**
         * @brief Attach standard type
         * @warning Be careful, if this data is in an allocation like a vector, its adress can change. This will break this attachement !
         * @param data 
         */
        // void attachStdType(double *data, bool isPrivate = false, bool isStatic = false)
        // {
        //     if(data == nullptr)
        //     {
        //         throw std::logic_error("Attach a nullptr as a std double");
        //     }

        //     mAttachedStdDoubles.push_back({isPrivate, isStatic, data});
        // }

        /**
         * @brief Attach a string element to this
         * @warning Be extremely careful: during string reallocations the adress of the string can change, this will break the attachement and cause bugs.
         * You should reserve enought space on your string before attaching it and perform a detach a reattach if its adress change
         * @param data 
         */
        // void attachStdType(std::string *data, bool isPrivate = false, bool isStatic = false)
        // {
        //     mAttachedStdString.push_back({isPrivate, isStatic, data});
        // }

        /**
         * @brief Detach a stdandard type from this
         * 
         * @param data 
         */
        // void detachStdType(int32_t *data);
        // void detachStdType(double *data);
        // void detachStdType(std::string *data);
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMPONENTS PARCOUR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        /**
         * @brief 
         * 
         * @tparam lambda 
         * @param func 
         */
        template<typename lambda>
        void parcourComponents(lambda&& func)
        {
            // static_assert(std::is_invocable_v<lambda, Iliade::GameComponent&>);
            func(this);
            for(auto &comp : mChildComponents)
            {
                comp->parcourComponents(func);
            }
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MODEL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Create a model from the non static data of the component
         * 
         * @return GameComponentModel 
         */
        GameComponentModel copyToModel();

        /**
         * @brief Serialise all the specific data of the component
         * @todo take account static and private data
         * @return std::vector<uint8_t> 
         */
        virtual std::vector<uint8_t> serialiseData()
        {
            std::vector<uint8_t> serialised;

            addValueToByteVector(mPositionX, serialised);
            addValueToByteVector(mPositionY, serialised);
            addValueToByteVector(mRotation , serialised);
            

            return std::move(serialised);
        }

        /**
         * @brief Deserialise the data and update the component data with it
         * 
         * @param data 
         * @return size of the data parsed
         */
        int updateFromData(std::vector<uint8_t> data)
        {

        }


        /**
         * @brief Deserialise the data and update the component data with it
         * 
         * @param data 
         * @todo Can be optimised
         */
        int updateFromData(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);

        /**
         * @brief Parse the data field of a serialised component
         * 
         * @param data 
         */
        virtual int parseData(std::vector<uint8_t> data)
        {
            parseData(data.begin(), data.end());
        }

        /**
         * @brief Parse the data field of a serialised component
         * 
         * @param data 
         * @return offset
         */
        virtual int parseData(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);




        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RUNTIME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        virtual void update(int deltaT)
        {
            for(auto &child : mChildComponents)
            {
                child->update(deltaT);
            }
        }

        virtual void show(Iliade::Graphics::IliadeGraphics &graphicEngine)
        {
            for(auto &child : mChildComponents)
            {
                child->show(graphicEngine);
            }
        }

    };

    

    

} // namespace Iliade




