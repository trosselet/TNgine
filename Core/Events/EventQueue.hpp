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

        struct Subscriber
        {
            uint64 Id;
            Callback Function;
        };

    public:

        void Push(const T& event)
        {
            m_Events.PushBack(event);
        }

        uint64 Subscribe(Callback callback)
        {
            uint64 id = m_NextId++;

            m_Subscribers.PushBack({ id, callback });

            return id;
        }

        void Unsubscribe(uint64 id)
        {
            for (uint64 i = 0; i < m_Subscribers.Size(); ++i)
            {
                if (m_Subscribers[i].Id == id)
                {
                    m_Subscribers.Erase(i);
                    return;
                }
            }
        }

        void Dispatch()
        {
            for (const auto& event : m_Events)
            {
                for (const auto& subscriber : m_Subscribers)
                {
                    subscriber.Function(event);
                }
            }

            m_Events.Clear();
        }

    private:

        uint64 m_NextId = 1;

        DynArray<T> m_Events;
        DynArray<Subscriber> m_Subscribers;
    };
}

#endif // !EVENT_QUEUE_H__INCLUDED
