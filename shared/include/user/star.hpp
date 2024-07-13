#pragma once

#include <core/GameComponent.hpp>
#include <graphics/SpriteAsset.hpp>

class Star : public Iliade::GameComponent
{
private:
    Iliade::Graphics::SpriteAsset mSprite;
    int mCpt = 0;
    int mSens = 0;
public:
    Star(Iliade::GameComponent *parentComponent, Iliade::Graphics::Sfml::SfmlIliadeGraphics &graphref) : Iliade::GameComponent(parentComponent), mSprite(this)
    {
        setPosition(1.5, 1.5);
        mSprite.setGroundIndex(2);

        Iliade::Graphics::Animation anim({{1, 1, 18, 18},
                                          {21, 1, 18, 18},
                                          {41, 1, 18, 18},
                                          {61, 1, 18, 18},
                                          {81, 1, 18, 18}});

        Iliade::Graphics::SpriteLayer layer0(std::make_unique<Iliade::Graphics::Sfml::SfmlSpriteRessource>(graphref, "../rsc/star.png"), {anim});
        mSprite.addLayer(std::move(layer0));

        mSprite.localStopAnimation();
        mSprite.localStartAnimation(0, 2);
    }   
    

    ~Star()
    {

    }

    void update(int deltaT) override
    {
        GameComponent::update(deltaT);
        mCpt+= deltaT;
        if(mCpt >= 100)
        {
            if(mSens == 0)
            {
                setPosition(getOffsetX(), getOffsetY() + 0.2);
                if(getOffsetY() > 3)
                {
                    mSens = 1;
                }

            }
            else
            {
                setPosition(getOffsetX(), getOffsetY() - 0.2);
                if(getOffsetY() < 0)
                {
                    mSens = 0;
                }
            }
            mCpt = 0;
        }
    }
};


