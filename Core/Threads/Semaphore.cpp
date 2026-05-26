#include "Semaphore.h"

TNgine::Semaphore::Semaphore(uint32 initialCount) : m_Semaphore(initialCount)
{
}

void TNgine::Semaphore::Release(uint32 count)
{
	m_Semaphore.release();
}

void TNgine::Semaphore::Acquire()
{
	m_Semaphore.acquire();
}
