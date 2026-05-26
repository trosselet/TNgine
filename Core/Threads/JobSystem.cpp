#include "JobSystem.h"

std::unique_ptr<TNgine::ThreadPool> TNgine::JobSystem::s_ThreadPool = nullptr;

void TNgine::JobSystem::Init(uint32 workerCount)
{
    s_ThreadPool = std::make_unique<ThreadPool>(workerCount);
}

void TNgine::JobSystem::Shutdown()
{
    s_ThreadPool.reset();
}

void TNgine::JobSystem::Execute(std::function<void()> task)
{
    if (s_ThreadPool)
    {
        s_ThreadPool->Submit(std::move(task));
    }
}

void TNgine::JobSystem::Wait()
{
    if (s_ThreadPool)
    {
        s_ThreadPool->WaitIdle();
    }
}
