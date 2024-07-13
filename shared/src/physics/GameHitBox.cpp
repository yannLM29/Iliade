#include "physics/GameHitBox.hpp"
#include "physics/GameElement.hpp"

namespace Iliade::Physics
{
    GameHitBox::GameHitBox(GameElement &parent, float w, float h, float offsetX, float offsetY, float angle) : mParentRef(parent), mW(w), mH(h)
    {
        b2PolygonShape mBoxShape;

        mBoxShape.SetAsBox(w / 2,h / 2,b2Vec2(offsetX, offsetY), angle);
        mBoxFixtureDef.shape = &mBoxShape;
        mBoxFixtureDef.density = 0.8;
        mBoxFixtureDef.friction = 0.20;
        mBoxFixtureDef.restitution = 0.4;
        // mBoxFixtureDef.filter = 
        // mBoxFixtureDef.isSensor = 
        mFixture = mParentRef.getBodyRef()->CreateFixture(&mBoxFixtureDef);
        
    }

    GameHitBox::~GameHitBox()
    {

    }
} // namespace Iliade::Physics
