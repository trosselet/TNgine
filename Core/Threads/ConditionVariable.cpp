#include "ConditionVariable.h"
#include "ConditionVariable.h"

void TNgine::ConditionVariable::NotifyOne()
{
	m_Condition.notify_one();
}

void TNgine::ConditionVariable::NotifyAll()
{
	m_Condition.notify_all();
}

void TNgine::ConditionVariable::Wait(std::unique_lock<std::mutex>& lock)
{
	m_Condition.wait(lock);
}
