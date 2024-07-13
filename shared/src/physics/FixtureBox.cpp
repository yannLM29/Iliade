#include "physics/FixtureBox.hpp"
#include "physics/GameElement.hpp"
#include "graphics/IliadeGraphics.hpp"

namespace Iliade::Physics
{
    FixtureBox::FixtureBox(GameElement &parent, float w, float h, float offsetX, float offsetY, 
                   float angle, float density, float friction, float restitution) : mParentRef(parent), mOffsetX(offsetX), mOffsetY(offsetY), mW(w), mH(h)
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

    FixtureBox::~FixtureBox()
    {
        mParentRef.getBodyRef()->DestroyFixture(mFixture);
    }

    void FixtureBox::display(Iliade::Graphics::IliadeGraphics &graphicEngine) const
    {
        auto pos = mParentRef.getBodyRef()->GetPosition();
        graphicEngine.render(Iliade::Graphics::DebugRect(pos.x + mOffsetX, pos.y + mOffsetY, mW, mH));
    }

} // namespace Iliade::Physics
