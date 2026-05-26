#include "Thread.h"

#include <chrono>

TNgine::Thread::~Thread()
{
    if (m_Thread.joinable())
    {
        m_Thread.join();
    }
}

void TNgine::Thread::Join()
{
    if (m_Thread.joinable())
    {
        m_Thread.join();
    }
}

void TNgine::Thread::Detach()
{
    if (m_Thread.joinable())
    {
        m_Thread.detach();
    }
}

bool TNgine::Thread::Joinable() const
{
    return m_Thread.joinable();
}

TNgine::Thread::ThreadID TNgine::Thread::GetID() const
{
    return m_Thread.get_id();
}

void TNgine::Thread::Sleep(uint32 ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void TNgine::Thread::Yield()
{
    std::this_thread::yield();
}
