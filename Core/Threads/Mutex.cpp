#include "Mutex.h"

void TNgine::Mutex::Lock()
{
    m_Mutex.lock();
}

void TNgine::Mutex::Unlock()
{
    m_Mutex.unlock();
}

bool TNgine::Mutex::TryLock()
{
    return m_Mutex.try_lock();
}
