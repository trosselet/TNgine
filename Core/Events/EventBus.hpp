#ifndef EVENT_BUS_H__INCLUDED
#define EVENT_BUS_H__INCLUDED

#include "EventQueue.hpp"

#include "Events.h" 

namespace TNgine
{
    class EventBus
    {
    public:

        EventQueue<KeyPressedEvent> KeyPressed;
        EventQueue<KeyReleasedEvent> KeyReleased;

        EventQueue<WindowCloseEvent> WindowClose;
        EventQueue<WindowResizeEvent> WindowResize;

    public:

        void Dispatch()
        {
            KeyPressed.Dispatch();
            KeyReleased.Dispatch();

            WindowClose.Dispatch();
            WindowResize.Dispatch();
        }
    };
}

#endif // !EVENT_BUS_H__INCLUDED