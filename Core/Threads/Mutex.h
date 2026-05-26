#ifndef MUTEX_H__INCLUDED
#define MUTEX_H__INCLUDED

#include <mutex>
#include "../PrimitivesTypes.h"

namespace TNgine
{
    class Mutex
    {
    public:

        void Lock();

        void Unlock();

        bool TryLock();

    private:

        std::mutex m_Mutex;

    private:
        friend class ThreadEvent;
        friend class ThreadPool;
    };
}

#endif // !MUTEX_H__INCLUDED