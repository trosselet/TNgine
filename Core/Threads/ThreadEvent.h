#ifndef THREAD_EVENT_H__INCLUDED
#define THREAD_EVENT_H__INCLUDED

#include "../PrimitivesTypes.h"
#include "Mutex.h"
#include "ConditionVariable.h"

namespace TNgine
{
    class ThreadEvent
    {
    public:

        void Signal();

        void Wait();

        void Reset();

    private:

        Mutex m_Mutex;

        ConditionVariable m_Condition;

        bool m_Signaled = false;
         
    };
}

#endif // !THREAD_EVENT_H__INCLUDED