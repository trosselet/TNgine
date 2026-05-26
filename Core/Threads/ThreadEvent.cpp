#include "ThreadEvent.h"

void TNgine::ThreadEvent::Signal()
{
    {
        std::lock_guard<std::mutex> lock(m_Mutex.m_Mutex);

        m_Signaled = true;
    }

    m_Condition.NotifyAll();
}

void TNgine::ThreadEvent::Wait()
{
    std::unique_lock<std::mutex> lock(m_Mutex.m_Mutex);

    m_Condition.Wait(lock, [this]()
    {
        return m_Signaled;
    });
}

void TNgine::ThreadEvent::Reset()
{
    std::lock_guard<std::mutex> lock(m_Mutex.m_Mutex);

    m_Signaled = false;
}
