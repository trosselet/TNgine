#ifndef THREAD_H__INCLUDED
#define THREAD_H__INCLUDED

#include <thread>
#include "../PrimitivesTypes.h"

namespace TNgine
{
    class Thread
    {
    public:
        using ThreadID = std::thread::id;
    public:

        Thread() = default;

        template<typename Fn>
        Thread(Fn&& fn) : m_Thread(std::forward<Fn>(fn))
        {
        }

        Thread(Thread&& other) noexcept : m_Thread(std::move(other.m_Thread))
        {
        }

        Thread& operator=(Thread&& other) noexcept
        {
            m_Thread = std::move(other.m_Thread);

            return *this;
        }

        Thread(const Thread&) = delete;

        Thread& operator=(const Thread&) = delete;

        ~Thread();

        void Join();

        void Detach();

        bool Joinable() const;

        ThreadID GetID() const;

        static void Sleep(uint32 ms);

        static void Yield();


    private:

        std::thread m_Thread;
    };
}

#endif // !THREAD_H__INCLUDED