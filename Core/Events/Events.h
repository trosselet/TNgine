#ifndef EVENTS_H__INCLUDED
#define EVENTS_H__INCLUDED

#include "../TMath.h"

namespace TNgine
{
    enum class EventType
    {
        None = 0,

        KeyPressed,
        KeyReleased,

        WindowClose,
        WindowResize
    };

    struct Event
    {
        EventType Type = EventType::None;
    };

    struct KeyPressedEvent : public Event
    {
        int32 Key = 0;
        bool Repeat = false;

        KeyPressedEvent()
        {
            Type = EventType::KeyPressed;
        }

        KeyPressedEvent(int32 key, bool repeat) : Key(key), Repeat(repeat)
        {
            Type = EventType::KeyPressed;
        }
    };

    struct KeyReleasedEvent : public Event
    {
        int32 Key = 0;

        KeyReleasedEvent()
        {
            Type = EventType::KeyReleased;
        }

        KeyReleasedEvent(int32 key) : Key(key)
        {
            Type = EventType::KeyReleased;
        }
    };

    struct WindowCloseEvent : public Event
    {
        WindowCloseEvent()
        {
            Type = EventType::WindowClose;
        }
    };

    struct WindowResizeEvent : public Event
    {
        uint32 Width = 800;
        uint32 Height = 600;

        WindowResizeEvent()
        {
            Type = EventType::WindowResize;
        }

        WindowResizeEvent(uint32 width, uint32 height) : Width(width), Height(height)
        {
            Type = EventType::WindowResize;
        }
    };
}





#endif // !EVENTS_H__INCLUDED
