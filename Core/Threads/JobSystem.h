#ifndef JOB_SYSTEM_H__INCLUDED
#define JOB_SYSTEM_H__INCLUDED

#include "../PrimitivesTypes.h"
#include "ThreadPool.h"
#include <functional>

namespace TNgine
{
    class JobSystem
    {
    public:

        static std::unique_ptr<TNgine::ThreadPool> s_ThreadPool;

        static void Init(uint32 workerCount);

        static void Shutdown();

        static void Execute(std::function<void()> task);

        static void Wait(); 
    };
}

#endif // !JOB_SYSTEM_H__INCLUDED