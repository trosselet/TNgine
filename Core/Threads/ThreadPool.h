#ifndef THREAD_POOL_H__INCLUDED
#define THREAD_POOL_H__INCLUDED

#include "../Containers/DynArray.hpp"
#include "Thread.h"
#include "Mutex.h"
#include "ConditionVariable.h"
#include "Atomic.h"

#include <queue>
#include <functional>

namespace TNgine
{
    class ThreadPool
    {
    public:

        ThreadPool(uint32 threadCount);

        ~ThreadPool();

        void Submit(std::function<void()> task);

        void WaitIdle();

    private:

        DynArray<Thread> m_Workers;

        std::queue<std::function<void()>> m_Tasks;

        Mutex m_Mutex;

        ConditionVariable m_Condition;

        Atomic<bool> m_Running = true;

        Atomic<uint32> m_ActiveTasks = 0;
    };
}


#endif //!THREAD_POOL_H__INCLUDED