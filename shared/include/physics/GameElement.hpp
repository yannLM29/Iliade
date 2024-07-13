/**
 * ... 
*/

#pragma once

#include <box2d/box2d.h>
#include <vector>

#include "core/GameComponent.hpp"
#include "physics/FixtureBox.hpp"
#include "physics/GameFixture.hpp"

namespace Iliade::Physics
{

    class GameElement : public GameComponent
    {
    private:
        b2World *worldRef;
        
        b2BodyDef mBodyDef;
        b2Body *mBody;

        std::vector<GameFixture> mFixtures;

    public:
        GameElement(GameScene &scene, bool isPStatic = false);
        GameElement(GameComponent *parentComponent, bool isPrivate = false, bool isPStatic = false);
        // ~GameElement();

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        b2World *getWorldRef()
        {
            return worldRef;
        }

        b2Body *getBodyRef()
        {
            return mBody;
        }

        void update(int deltaT) override;

        void addFixture(Iliade::Physics::GameFixture newFixture);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline void setPosition(float x, float y) noexcept override
        {
            GameComponent::setPosition(x, y);
            mBody->SetTransform(b2Vec2(x, y), mBody->GetAngle());
            
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RUNTIME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void show(Iliade::Graphics::IliadeGraphics &graphicEngine) override;

        int parseData(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) override; 

    private:
        void createBody(bool isPStatic = false);
    };
    
} // namespace Iliade::Physics
