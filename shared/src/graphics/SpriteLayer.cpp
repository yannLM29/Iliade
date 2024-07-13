#include "graphics/SpriteLayer.hpp"
#include "graphics/IliadeGraphics.hpp"
#include "core/IliadeEngine.hpp"

namespace Iliade::Graphics
{
    void SpriteLayer::setFrame(int currentFrame, int animationIndex)
    {
        if(animationIndex >= static_cast<int>(mAnimations.size()))
        {
            throw std::logic_error("Animation index is bigger than animation list");
        }

        mSelectedAnimation = animationIndex == -1 ? mSelectedAnimation : animationIndex;        // if no animation is selected, we choose the current animation
        
        if(mCurrentFrameIndex >= mAnimations[mSelectedAnimation].frames.size())
        {
            throw std::logic_error("Frame index is bigger than animation list");
        }
        mCurrentFrameIndex = currentFrame;
        mSpriteImplem->setFrame(mAnimations[mSelectedAnimation].frames[mCurrentFrameIndex]);
    }


    void SpriteLayer::display(IliadeGraphics &graphicEngine)
    {  
        
        graphicEngine.render(*this);
    }
    

    void SpriteLayer::updateAnimation()
    {
        mCurrentFrameIndex++;
        if(mCurrentFrameIndex >= mAnimations[mSelectedAnimation].frames.size())
        {
            mCurrentFrameIndex = 0;
        }

        mSpriteImplem->setFrame(mAnimations[mSelectedAnimation].frames[mCurrentFrameIndex]);
    }

} // namespace Iliade::graphics
