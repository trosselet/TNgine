#include "ThreadPool.h"

TNgine::ThreadPool::ThreadPool(uint32 threadCount)
{
    m_Workers.Reserve(threadCount);
    for (uint32 i = 0; i < threadCount; ++i)
    {
        m_Workers.PushBack(Thread([this]()
        {
            while (m_Running)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(m_Mutex.m_Mutex);

                    m_Condition.Wait(lock, [this]()
                        {
                            return !m_Tasks.empty() || !m_Running;
                        });

                    if (!m_Running)
                    {
                        return;
                    }

                    task = std::move(m_Tasks.front());
                    m_Tasks.pop();

                    ++m_ActiveTasks;
                }

                task();

                --m_ActiveTasks;
            }
        }));
    }
}

TNgine::ThreadPool::~ThreadPool()
{
    m_Running = false;

    m_Condition.NotifyAll();

    for (auto& worker : m_Workers)
    {
        if (worker.Joinable())
        {
            worker.Join();
        }
    }
}

void TNgine::ThreadPool::Submit(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> lock(m_Mutex.m_Mutex);

        m_Tasks.push(std::move(task));
    }

    m_Condition.NotifyOne();
}

void TNgine::ThreadPool::WaitIdle()
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(m_Mutex.m_Mutex);

            if (m_Tasks.empty() && m_ActiveTasks == 0)
            {
                break;
            }
        }

        std::this_thread::yield();
    }
}
