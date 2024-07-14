#pragma once

#include <core/IliadeEngine.hpp>
#include <core/GameComponent.hpp>
#include <core/ExternalTypeComponent.hpp>
#include <graphics/SpriteAsset.hpp>
#include <graphics/SpriteLayer.hpp>
#include <graphics/sfml/SfmlSpriteRessource.hpp>
#include <inputs/ReceivedInputManager.hpp>
#include <core/PlayableElement.hpp>

#include <memory>
#include <vector>

#include "user/star.hpp"

enum eWalkDir {
    kStand = 0,
    kRight,
    kLeft,
    kUp,
    kDown
};

class Character : public Iliade::PlayableElement
{
private:
    Iliade::Graphics::SpriteAsset mSprite;
    eWalkDir isWalking = kStand;
    Star mStar;

public:
    Character(Iliade::GameScene &scene, Iliade::Graphics::Sfml::SfmlIliadeGraphics &graphref) : Iliade::PlayableElement(scene), mSprite(this), mStar(this, graphref)
    {
        Iliade::Graphics::Animation anim_turn({{4,   2, 22, 37},
                                               {46,  2, 22, 37},
                                               {88,  2, 22, 37},
                                               {130, 2, 22, 37},
                                               {172, 2, 22, 37},
                                               {214, 2, 22, 37},
                                               {255, 2, 22, 37},
                                               {298, 2, 22, 37}});

        Iliade::Graphics::Animation anim_walk_right({{4,   240, 22, 37},
                                                     {46,  240, 22, 37},
                                                     {88,  241, 27, 37},
                                                     {130, 240, 22, 37},
                                                     {172, 240, 22, 37},
                                                     {214, 240, 22, 37},
                                                     {255, 240, 27, 37},
                                                     {298, 240, 22, 37}});

        Iliade::Graphics::Animation anim_walk_left({{2,   404, 22, 37},
                                                    {44,  404, 22, 37},
                                                    {86,  404, 22, 37},
                                                    {128, 404, 22, 37},
                                                    {170, 404, 22, 37},
                                                    {212, 404, 22, 37},
                                                    {253, 404, 22, 37},
                                                    {296, 404, 22, 37}});
        

        Iliade::Graphics::Animation anim_walk_down({{1, 322, 28, 37},
                                                    {45, 322, 24, 37},
                                                    {88, 322, 22, 37},
                                                    {129, 323, 24, 37},
                                                    {169, 322, 28, 37},
                                                    {213, 322, 24, 37},
                                                    {255, 322, 24, 37},
                                                    {297, 322, 24, 37}});

        Iliade::Graphics::Animation anim_walk_up({{1,   158, 28, 37},
                                                  {45,  158, 24, 37},
                                                  {88,  158, 22, 37},
                                                  {129, 158, 24, 37},
                                                  {169, 158, 28, 37},
                                                  {213, 158, 24, 37},
                                                  {255, 158, 24, 37},
                                                  {297, 158, 24, 37}});

        Iliade::Graphics::Animation stopedRight({{90,  2,   19, 37}});
        Iliade::Graphics::Animation stopedLeft({{257, 2,   19, 37}});
        Iliade::Graphics::Animation stopedDown({{172, 2, 22, 37}});
        Iliade::Graphics::Animation stopedUp({{4,   2, 22, 37}});
        


        Iliade::Graphics::SpriteLayer layer0(std::make_unique<Iliade::Graphics::Sfml::SfmlSpriteRessource>(graphref, "../rsc/mario.png"), {anim_turn, anim_walk_right, anim_walk_left, anim_walk_down, anim_walk_up, stopedRight, stopedLeft, stopedDown, stopedUp});
       
        mSprite.addLayer(std::move(layer0));
        mSprite.setGroundIndex(1);


        addFixture(Iliade::Physics::GameFixture(std::make_unique<Iliade::Physics::FixtureBox>(*this, 1.5, 2.5)));
    }

    ~Character()
    {

    }



    inline Iliade::Graphics::SpriteAsset& getSpriteRef() noexcept
    {
        return mSprite;
    }

    void setAnimSpeed(float speed)
    {
        mSprite.setAnimSpeed(speed);
    }
    void moveLeft()
    {
        if(isWalking != kLeft)
        {
            mSprite.localStartAnimation(2, 15);
            mSprite.startAnimation(2, 15);
            isWalking = kLeft;
            mSprite.setAnimSpeed(3);
        }

        if(mSprite.getAnimSpeed() < 15)
            mSprite.setAnimSpeed(mSprite.getAnimSpeed() + 2);
        

        getBodyRef()->ApplyForce(b2Vec2(-15, 0),getBodyRef()->GetWorldCenter(), true);
        
    }

    void moveRight()
    {
        if(isWalking != kRight)
        {
            mSprite.localStartAnimation(1, 15);
            mSprite.startAnimation(1, 15);
            isWalking = kRight;
            mSprite.setAnimSpeed(3);
        }

        if(mSprite.getAnimSpeed() < 15)
            mSprite.setAnimSpeed(mSprite.getAnimSpeed() + 2);

        // setPosition(getPositionX() + 1, getPositionY());
        getBodyRef()->ApplyForce(b2Vec2(15, 0),getBodyRef()->GetWorldCenter(), true);
        
    
    }

    void moveDown()
    {
        if(isWalking != kDown)
        {
            mSprite.localStartAnimation(3, 15);
            mSprite.startAnimation(3, 15);
            isWalking = kDown;
            mSprite.setAnimSpeed(3);
        }

        if(mSprite.getAnimSpeed() < 15)
            mSprite.setAnimSpeed(mSprite.getAnimSpeed() + 2);

        // setPosition(getPositionX(), getPositionY()+1);
        // mSprite.setPosition(getPositionX(), getPositionY()+1);
    }

    void moveUp()
    {
        if(isWalking != kUp)
        {
            mSprite.localStartAnimation(4, 15);
            mSprite.startAnimation(4, 15);
            isWalking = kUp;
            mSprite.setAnimSpeed(3);
        }

        if(mSprite.getAnimSpeed() < 15)
            mSprite.setAnimSpeed(mSprite.getAnimSpeed() + 2);

        getBodyRef()->ApplyLinearImpulseToCenter(b2Vec2(0, 10), true);

    }

    void stop()
    {   
        getBodyRef()->SetLinearVelocity(b2Vec2(0, getBodyRef()->GetLinearVelocity().y));
        mSprite.localStopAnimation();
        mSprite.stopAnimation(false);
        if(isWalking == kRight)
        {
            mSprite.chooseAnimation(5);
        }
        else if(isWalking == kLeft)
        {
            mSprite.chooseAnimation(6);
        }
        else if(isWalking == kDown)
        {
            mSprite.chooseAnimation(7);
        }
        else if(isWalking == kUp)
        {
            mSprite.chooseAnimation(8);
        }
        
        mSprite.localStopAnimation();
        isWalking = kStand;
    }

    void interact(const Iliade::Inputs::ReceivedInputManager &inputManager, int deltaT)
    {
        auto events = inputManager.getEvents();

        // getEngineRef().log("interacting !");
        inputManager.print();
        for(const Iliade::Inputs::InputEvent &event : events)
        {
            switch (event.status)
            {

                case Iliade::Inputs::eInputStatus::kPressed:
                    if(event.code == Iliade::Inputs::eInputCode::kQ)
                    {
                        moveLeft();
                    }
                    else if(event.code == Iliade::Inputs::eInputCode::kD)
                    {
                        moveRight();
                    }
                    else if(event.code == Iliade::Inputs::eInputCode::kS)
                    {
                        moveDown();
                    }
                    else if(event.code == Iliade::Inputs::eInputCode::kZ)
                    {
                        moveUp();
                    }
                    if(event.code == Iliade::Inputs::eInputCode::kMouseLeft)
                    {
                        getEngineRef().debugLog("x=" + std::to_string(inputManager.getLocalMousePositionX()) + " y=" + std::to_string(inputManager.getLocalMousePositionY()));
                    }
                    break;

                case Iliade::Inputs::eInputStatus::kStillPressed:
                    if(event.code == Iliade::Inputs::eInputCode::kQ)
                    {
                        moveLeft();
                    }
                    else if(event.code == Iliade::Inputs::eInputCode::kD)
                    {
                        moveRight();
                    }
                    else if(event.code == Iliade::Inputs::eInputCode::kS)
                    {
                        moveDown();
                    }
                    else if(event.code == Iliade::Inputs::eInputCode::kZ)
                    {
                        moveUp();
                    }
                    
                    break;

                case Iliade::Inputs::eInputStatus::kReleased:
                    if(event.code == Iliade::Inputs::eInputCode::kQ || event.code == Iliade::Inputs::eInputCode::kD 
                    || event.code == Iliade::Inputs::eInputCode::kS || event.code == Iliade::Inputs::eInputCode::kZ)
                    {
                        stop();
                    }
                    break;

                default:
                    break;
            }
        }
    }

    inline Star &getStar() noexcept
    {
        return mStar;
    }
};

