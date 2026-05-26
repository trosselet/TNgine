#ifndef SPINLOCK_H__INCLUDED
#define SPINLOCK_H__INCLUDED

#include "../PrimitivesTypes.h"
#include <atomic>

namespace TNgine
{
    class SpinLock
    {
    public:

        void Lock();

        void Unlock();

    private:

        std::atomic_flag m_Flag = ATOMIC_FLAG_INIT;
    };
}

#endif // !SPINLOCK_H__INCLUDED