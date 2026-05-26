#ifndef CONDITION_VARIABLE_H__INCLUDED
#define CONDITION_VARIABLE_H__INCLUDED

#include "../PrimitivesTypes.h"
#include <condition_variable>

namespace TNgine
{
    class ConditionVariable
    {
    public:

        void NotifyOne();

        void NotifyAll();

        void Wait(std::unique_lock<std::mutex>& lock);

        template<typename Predicate>
        void Wait(std::unique_lock<std::mutex>& lock, Predicate pred);

    private:

        std::condition_variable m_Condition;
    };

    template<typename Predicate>
    void ConditionVariable::Wait(std::unique_lock<std::mutex>& lock, Predicate pred)
    {
        m_Condition.wait(lock, pred);
    }
}

#endif // !CONDITION_VARIABLE_H__INCLUDED