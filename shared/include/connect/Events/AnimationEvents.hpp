/**
 * @file AnimationEvents.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <cstdint>
#include "utils/BitManips.hpp"
#include "connect/Events/Event.hpp"

namespace Iliade::Connect::Events
{
    class StartAnimEvent : public Event
    {
    private:
        int32_t mId;
        int32_t mAnimationIndex;
        float mSpeed;
        uint8_t mIsOneShot;
        uint8_t mCutLast;
    public:
        StartAnimEvent(int32_t id, int32_t animationIndex, float speed, bool isOneShot = false, bool cutLast = true) : Event(kStartAnim, 14),
            mId(id), mAnimationIndex(animationIndex), mSpeed(speed), mIsOneShot(isOneShot), mCutLast(cutLast)
        {
        } 

        StartAnimEvent(const std::vector<uint8_t> &dataIn) : Event(kStartAnim, 14)
        {
            if(dataIn.size() < 14)
            {
                throw std::runtime_error("dataIn is too short");
            }

            mId = readInt32ValueFromByteVector(dataIn.cbegin());
            mAnimationIndex = readInt32ValueFromByteVector(dataIn.cbegin() + 4);
            mSpeed = readFloatValueFromByteVector(dataIn.cbegin() + 8);
            mIsOneShot = dataIn[12];
            mCutLast = dataIn[13];

        }

        // ~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~
        inline int getId() const noexcept
        {
            return mId;
        }
        
        inline int getAnimationIndex() const noexcept 
        {
            return mAnimationIndex;
        }

        inline float getSpeed() const noexcept 
        {
            return mSpeed;
        }

        inline uint8_t getIsOneShot() const noexcept 
        {
            return mIsOneShot;
        }

        inline uint8_t getCutLast() const noexcept 
        {
            return mCutLast;
        }

        // ~~~~~~~~~~~~~~~~~~~ SERIALISE ~~~~~~~~~~~~~~~~~~
        std::vector<uint8_t> serialise() const noexcept
        {
            std::vector<uint8_t> r = Event::serialise();
            addValueToByteVector(mId, r);
            addValueToByteVector(mAnimationIndex, r);
            addValueToByteVector(mSpeed, r);
            addValueToByteVector(mIsOneShot, r);
            addValueToByteVector(mCutLast, r);

            return std::move(r);            
        }

    };

    class ChangeAnimSpeed : public Event
    {
    private:
        int32_t mId;
        float mSpeed;

    public:
        ChangeAnimSpeed(int32_t id, float speed) : Event(kChangeAnimSpeed, 8), mId(id), mSpeed(speed)
        {

        }

        ChangeAnimSpeed(const std::vector<uint8_t> &dataIn) : Event(kChangeAnimSpeed, 8)
        {
            if(dataIn.size() < getSize())
            {
                throw std::runtime_error("dataIn is too short");
            }

            mId = readInt32ValueFromByteVector(dataIn.cbegin() + 0);
            mSpeed = readFloatValueFromByteVector(dataIn.cbegin() + 4);
        }

        inline int getId() const noexcept
        {
            return mId;
        }

        inline float getSpeed() const noexcept 
        {
            return mSpeed;
        }

        std::vector<uint8_t> serialise() const noexcept
        {
            std::vector<uint8_t> r = Event::serialise();
            addValueToByteVector(mId, r);
            addValueToByteVector(mSpeed, r);
            return std::move(r);
        }

    };

    class StopAnimEvent : public Event
    {
    private:
        int32_t mId;
        uint8_t mCutLast;

    public:
        StopAnimEvent(int32_t id, uint8_t cutLast) : Event(kStopAnim, 5), mId(id), mCutLast(cutLast)
        {

        }

        StopAnimEvent(const std::vector<uint8_t> &dataIn) : Event(kStopAnim, 5)
        {
            if(dataIn.size() < getSize())
            {
                throw std::runtime_error("dataIn (" + std::to_string(dataIn.size()) + " bytes) is too short, should be " + std::to_string(getSize()));
            }

            mId = readInt32ValueFromByteVector(dataIn.cbegin() + 0);
            mCutLast = dataIn[4];
        }

         // ~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~
        inline int getId() const noexcept
        {
            return mId;
        }

        inline uint8_t getCutLast() const noexcept 
        {
            return mCutLast;
        }

         // ~~~~~~~~~~~~~~~~ SERIALISE ~~~~~~~~~~~~~~~~
        std::vector<uint8_t> serialise() const noexcept
        {
            std::vector<uint8_t> r = Event::serialise();
            addValueToByteVector(mId, r);
            addValueToByteVector(mCutLast, r);
            return std::move(r);
        }

    };
    
} // namespace Iliade::Connect
