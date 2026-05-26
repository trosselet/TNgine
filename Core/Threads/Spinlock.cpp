#include "Spinlock.h"

void TNgine::SpinLock::Lock()
{
    while (m_Flag.test_and_set(std::memory_order_acquire))
    {
    }
}

void TNgine::SpinLock::Unlock()
{
    m_Flag.clear(std::memory_order_release);
}
