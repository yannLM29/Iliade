#include "physics/GameElement.hpp"
#include "physics/GameHitBox.hpp"
#include "core/GameScene.hpp"
#include "graphics/IliadeGraphics.hpp"
#include "graphics/SpriteAsset.hpp"
#include "core/IliadeEngine.hpp"

namespace Iliade::Physics
{
    GameElement::GameElement(GameScene &scene, bool isPStatic ) : Iliade::GameComponent(scene)
    {
        createBody(isPStatic);

    }

    GameElement::GameElement(GameComponent *parentComponent, bool isPrivate, bool isPStatic) : Iliade::GameComponent(parentComponent, isPrivate)
    {
        createBody(isPStatic);
    }

    void GameElement::createBody(bool isPStatic)
    {
        auto &worldRef = getParentScene()->getPhysicsEngineRef().getWorldRef();

        mBodyDef.type = !isPStatic ? b2_dynamicBody : b2_staticBody; 
        mBodyDef.position.Set(0, 0);
        mBodyDef.angle = 0;

        mBody = worldRef.CreateBody(&mBodyDef);
        mBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
    }

    void GameElement::update(int deltaT)
    {
        Iliade::GameComponent::update(deltaT);

        setPosition(mBody->GetPosition().x, mBody->GetPosition().y);
        setRotation(mBody->GetAngle());
    }

    void GameElement::addFixture(GameFixture newFixture)
    {
        mFixtures.emplace_back(std::move(newFixture));
    }

    void GameElement::show(Iliade::Graphics::IliadeGraphics &graphicEngine)
    {
        GameComponent::show(graphicEngine);
        for(auto &fixture : mFixtures)
        {
            graphicEngine.show(fixture);
        }
        
    }

    int GameElement::parseData(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) 
    {
        int r = Iliade::GameComponent::parseData(begin, end);     
        mBody->SetTransform(b2Vec2(getPositionX(), getPositionY()), getRotation());

        return r;
    }

}