/**
 * @file ReaderWriterLock.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-07-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <semaphore>
#include <mutex>
#include <vector>

namespace Iliade
{
    class ReaderWriterLock
    {
    private:
        int mNumberOfReaders;
        std::mutex mNumberOfReadersMutex;
        std::mutex mBeginMutex;
        std::binary_semaphore mWriterSem;

    public:
        ReaderWriterLock() : mWriterSem(1)
        {

        }
        
        void begin_read()
        {
            mBeginMutex.lock();
                mNumberOfReadersMutex.lock();
                    if(mNumberOfReaders == 0)
                    {
                        mWriterSem.acquire();
                    }
                    mNumberOfReaders++;
                mNumberOfReadersMutex.unlock();
            mBeginMutex.unlock();

        }

        void end_read()
        {
            mNumberOfReadersMutex.lock();
                mNumberOfReaders--;
                if(mNumberOfReaders == 0)
                {
                    mWriterSem.release();
                }
            mNumberOfReadersMutex.unlock();
        }

        void begin_write()
        {
            mBeginMutex.lock();
                mWriterSem.acquire();
            mBeginMutex.unlock();
        }

        void end_write()
        {
            mWriterSem.release();
        }
    };
} // namespace Iliade