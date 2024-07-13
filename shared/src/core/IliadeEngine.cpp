/**
 * @file IliadeEngine.cpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-04-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include <algorithm>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "core/IliadeEngine.hpp"
#include "core/GameComponent.hpp"
#include "core/GameScene.hpp"

#include "graphics/IliadeGraphics.hpp"

namespace Iliade
{
    IliadeEngine::IliadeEngine() : mLastComponentId(0)
    {

    }

    IliadeEngine::~IliadeEngine()
    {

    }

    bool IliadeEngine::addScene(GameScene *scene)
    {
        if(scene == nullptr)
        {
            throw std::invalid_argument("Scene can't be nullptr");
        }
        
        auto scenes_it = std::find_if(mScenes.cbegin(), mScenes.cend(), [&](auto &aScene){
            return aScene->getId() == scene->getId();
        });

        if(scenes_it == mScenes.cend())
        {
            mScenes.emplace_back(scene);
            return true;
        }
        return false;
    }


    bool IliadeEngine::removeScene(int sceneId)
    {

        auto scenes_it = mScenes.erase(std::remove_if(mScenes.begin(), mScenes.end(), [&](auto &aScene){
            return aScene->getId() == sceneId;
        }));

        return scenes_it == mScenes.end() ? 0 : 1;

    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GRAPHICS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void IliadeEngine::show(GameScene &scene)
    {
        mGraphicEngine->clearWindow();
        scene.show(*mGraphicEngine);
        mGraphicEngine->renderWindow();
    }


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LOG SYSTEM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void IliadeEngine::log(std::string text)
    {
        std::cout << "log: " << getDateAndTime() << " - " << text << std::endl;
    }

    void IliadeEngine::debugLog(std::string text, std::any caller)
    {
        #ifdef DEBUG
        std::string typeName{caller.type().name()};
        debugLog("From " + typeName + " : " + text);
        #endif
    }

    void IliadeEngine::debugLog(std::string text)
    {
        #ifdef DEBUG
        std::cout << "debug: " << getDateAndTime() << " - " << text << std::endl;
        #endif
    }

    void IliadeEngine::errorLog(std::string text)
    {
        std::cerr << "\033[41merror:\033[0m " << getDateAndTime() << " - " << text << std::endl;
    }
    
    void IliadeEngine::errorLog(int errorCode, std::string text)
    {
        std::cerr << "\033[41merror: code " << errorCode << "\033[0m " << getDateAndTime() << " - " << text << std::endl;
    }

    void IliadeEngine::logIliadeStartUpInfo()
    {
        std::cout << "\033[104m\033[1m                  Iliade Engine version " << getVersion() << "                    \033[0m" << std::endl;
    }

    void IliadeEngine::warningLog(std::string text)
    {
        std::cerr << "\033[43mwarning:\033[0m " << getDateAndTime() << " - " << text << std::endl;
    }

    std::string IliadeEngine::getDateAndTime() const
    {
        std::stringstream r;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        
        r << std::setw(2) << std::setfill('0') << ltm->tm_mday << "/" 
        << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon << "/" 
        << 1900 + ltm->tm_year << " ";

        if (ltm->tm_hour < 10) 
        {
            r << "0";
        }

        r << ltm->tm_hour << ":";
        
        if (ltm->tm_min < 10) 
        {
            r << "0";
        }

        r << ltm->tm_min;
        
        return r.str();
    }

} // namespace Iliade
