#ifndef EVENT_QUEUE_H__INCLUDED
#define EVENT_QUEUE_H__INCLUDED

#include "../Containers/DynArray.hpp"

namespace TNgine
{
    template<typename T>
    class EventQueue
    {
    public:

        using EventType = T;
        using Callback = void(*)(const EventType&);

    public:

        void PushEvent(const EventType& event)
        {
            m_Events.PushBack(event);
        }

        Callback Subscribe(Callback callback)
        {
            m_Callbacks.PushBack(callback);
            return callback;
        }

        void Unsubscribe(Callback callback)
        {
            for (uint64 i = 0; i < m_Callbacks.Size(); ++i)
            {
                if (m_Callbacks[i] == callback)
                {
                    m_Callbacks.Erase(i);
                    return;
                }
            }
        }

        void Dispatch()
        {
            for (const auto& event : m_Events)
            {
                for (const auto& callback : m_Callbacks)
                {
                    callback(event);
                }
            }

            m_Events.Clear();
        }

    private:

        DynArray<EventType> m_Events;
        DynArray<Callback> m_Callbacks;
    };
}

#endif // !EVENT_QUEUE_H__INCLUDED
