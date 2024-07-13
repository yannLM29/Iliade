/**
 * @file GameScene.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-04-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string>
#include <vector>

#include "core/IContext.hpp"
#include "core/GameSceneModel.hpp"
#include "physics/IliadePhysics.hpp"


namespace Iliade::Graphics
{
    class IliadeGraphics;
} // namespace Iliade::Graphics

namespace Iliade
{
    class GameComponent;
    class IliadeEngine;
    class PlayableComponent;

    /**
     * @brief Game Scene
     * 
     */
    class GameScene : public IContext
    {
    private:
        int mId;
        std::vector<GameComponent*> mComponents;
        IliadeEngine &mEngineRef;
        Iliade::Physics::IliadePhysics mPhysicEngine;

    public:

        /**
         * @brief Create Iliade Engine, Must be instanciate only one time
         * 
         */
        GameScene(IliadeEngine& engine, float gravityX = 0, float gravityY = -9.8);

        /**
         * @brief Destroy the Iliade Engine object
         * 
         */
        ~GameScene();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline IliadeEngine& getEngineRef() const noexcept
        {
            return mEngineRef;
        }

        inline int getId() const noexcept
        {
            return mId;
        }

        inline std::vector<GameComponent*>& getComponents() noexcept
        {
            return mComponents;
        }

        GameComponent* getComponentById(int id);

        std::string getComponentListDescription();


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMPONENT MANAGEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /**
         * @brief Add a new component in the scene root list of components mandatory to be synchronised
         * 
         * @param newComponent Adress of the new component to add
         */
        void addComponent(GameComponent *newComponent);

        /**
         * @brief 
         * 
         * @param componentId 
         */
        void removeComponent(GameComponent *componentToRemove);


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMPONENTS PARCOUR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        template<typename lambda>
        void parcourComponents(lambda&& func_)
        {
            // static_assert(std::is_invocable_v<lambda, Iliade::GameComponent&>);
            
            for(auto &comp_ : mComponents)
            {
                comp_->parcourComponents(func_);
            }
        }


        template<typename lambda>
        std::vector<int> getVisibleComponentsList(lambda&& lamb) const
        {
            std::vector<int> visibleIdList;

            auto scene_lambda = [&](auto the_comp){
                if(lamb(the_comp) == true)
                {
                    visibleIdList.emplace_back(the_comp->getId());
                }
            };

            for(auto &comp : mComponents)
            {
                comp->parcourComponents(scene_lambda);
            }

            return std::move(visibleIdList);
        }

        Iliade::Physics::IliadePhysics &getPhysicsEngineRef() noexcept
        {
            return mPhysicEngine;
        }


        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MODEL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Create of model from the non static data of the scene
         * 
         * @return GameSceneModel 
         */
        GameSceneModel copyToModel();

        /**
         * @brief Deserialise the data and update the scene data with it
         * @todo Need to be optimized
         * @param data 
         */
        void updateFromData(std::vector<uint8_t> data);



        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RUNTIME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        void update(int deltaT);
        void show(Iliade::Graphics::IliadeGraphics &graphicEngine);

    };

} // namespace iliade




