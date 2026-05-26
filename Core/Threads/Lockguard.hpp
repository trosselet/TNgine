#ifndef LOCKGUARD_H__INCLUDED
#define LOCKGUARD_H__INCLUDED
 
#include "../PrimitivesTypes.h"

namespace TNgine
{
    template<typename T>
    class LockGuard
    {
    public:

        LockGuard(T& mutex) : m_Mutex(mutex)
        {
            m_Mutex.Lock();
        }

        ~LockGuard()
        {
            m_Mutex.Unlock();
        }

    private:

        T& m_Mutex;
    };
}

#endif // !LOCKGUARD_H__INCLUDED