#pragma once
#include <physics/GameElement.hpp>
#include <graphics/SpriteAsset.hpp>

class platformtest : public Iliade::Physics::GameElement 
{
private:
    Iliade::Graphics::SpriteAsset mSprite;
public:
    platformtest(Iliade::GameScene &scene, Iliade::Graphics::Sfml::SfmlIliadeGraphics &graphref) : Iliade::Physics::GameElement(scene, true), mSprite(this)
    {
        Iliade::Graphics::Animation defaultAnim({{0, 0, 114, 25}});
    
        Iliade::Graphics::SpriteLayer layer0(std::make_unique<Iliade::Graphics::Sfml::SfmlSpriteRessource>(graphref, "../rsc/platform1.png"), {defaultAnim});
       
        mSprite.addLayer(std::move(layer0));
        mSprite.setGroundIndex(0);

        addFixture(Iliade::Physics::GameFixture(std::make_unique<Iliade::Physics::FixtureBox>(*this, 7, 1)));

    }
    
};

