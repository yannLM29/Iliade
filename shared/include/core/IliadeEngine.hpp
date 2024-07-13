/**
 * @file IliadeEngine.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-04-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#define DEBUG

#include <string>
#include <vector>
#include <any>
#include <chrono>
#include <thread>

#include "IliadeVersion.hpp"

namespace Iliade::Graphics
{
    class IliadeGraphics;
} // namespace Iliade::Graphics

namespace Iliade::Connect
{
    class EventManager;
    class Event;
}

namespace Iliade
{
    class GameComponent;
    class GameScene;
    
    /**
     * @brief Iliade Game Engine object
     * 
     */
    class IliadeEngine
    {
    private:

        Graphics::IliadeGraphics *mGraphicEngine;
        std::unique_ptr<Connect::EventManager> mEventManager;

        int mLastSceneId;
        int mLastComponentId;
        std::vector<GameScene*> mScenes;

    public:

        /**
         * @brief Create Iliade Engine, Must be instanciate only one time
         * 
         */
        IliadeEngine();

        /**
         * @brief Destroy the Iliade Engine object
         * 
         */
        ~IliadeEngine();


        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Get the Version of Iliade Engine
         * 
         * @return std::string representing the version X.X.X
         */
        inline std::string getVersion() const noexcept
        {
            return std::to_string(getVersionMajor()) + "." + std::to_string(getVersionMinor()) + "." + std::to_string(getVersionPatch());
        }

        /**
         * @brief Get the Version of Iliade Engine
         * 
         * @return int representing the major value of version
         */
        inline int getVersionMajor() const noexcept
        {
            return ILIADE_VERSION_MAJOR;
        }

        /**
         * @brief Get the Version of Iliade Engine
         * 
         * @return int representing the minor value of version
         */
        inline int getVersionMinor() const noexcept
        {
            return ILIADE_VERSION_MINOR;
        }

        /**
         * @brief Get the Version of Iliade Engine
         * 
         * @return int representing the patch value of version
         */
        inline int getVersionPatch() const noexcept
        {
            return ILIADE_VERSION_PATCH;
        }

        inline const std::vector<GameScene*> &getScenes() const noexcept
        {
            return mScenes;
        }

        /**
         * @brief Get the Date And Time 
         * 
         * @return std::string DD/MM/YYYY hh:mm
         */
        std::string getDateAndTime() const;
        
        Iliade::Graphics::IliadeGraphics &getGraphicEngineRef()
        {
            return *mGraphicEngine;
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        inline void setGraphicEngine(Iliade::Graphics::IliadeGraphics &graphicEngine)
        {
            mGraphicEngine = &graphicEngine;
        }

        void setEventManager(std::unique_ptr<Iliade::Connect::EventManager> eventManager);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ID GENERATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Generate a new id for any new scene
         * 
         * @return int 
         */
        inline int generateNewSceneId() noexcept
        {
            return ++mLastSceneId;
        }

        /**
         * @brief Generate a new id for any new component
         * 
         * @return int 
         */
        inline int generateNewComponentId() noexcept
        {
            return ++mLastComponentId;
        }


        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SCENE ATTACHEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief Add a new scene in the engine list of scenes, mandatory to be synchronised
         * 
         * @param newComponent Adress of the new scene to add
         * @return bool Return false if the component is already in the list
         */
        bool addScene(GameScene *scene);

        /**
         * @brief Remove a scene from the list of synchronised lists
         * 
         * @param sceneId 
         * @return true The scene has been remove from the list
         * @return false The scene was not in the list
         */
        bool removeScene(int sceneId);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GRAPHICS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /**
         * @brief 
         * 
         */
        void show(GameScene &scene);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CONNECT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
        void sendEvent(std::unique_ptr<Connect::Event> event, int targetId = 0);
        void treatEvent(std::unique_ptr<Connect::Event> event);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LOG SYSTEM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void log(std::string text);

        void debugLog(std::string text, std::any caller);
        void debugLog(std::string text);

        template<typename T>
        void debugLogVar(T var)
        {
            debugLog(std::to_string(var));
        }

        template<typename T>
        void debugLogVar(std::string text, T var)
        {
            debugLog(text + std::to_string(var));
        }

        void errorLog(std::string text);
        void errorLog(int errorCode, std::string text);

        void warningLog(std::string text);

        void logIliadeStartUpInfo();

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SLEEP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        /**
         * @brief 
         * 
         * @param time in milliseconds
         */
        void sleep(int time)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }
    };

} // namespace iliade




