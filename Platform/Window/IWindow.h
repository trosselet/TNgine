#ifndef WINDOW_INTERFACE_H__INCLUDED
#define WINDOW_INTERFACE_H__INCLUDED

#include <Core/include.h>

namespace TNgine
{
	enum class WindowMode
	{
		Windowed,
		Borderless,
		Fullscreen
	};

	class IWindow
	{
	public:

		IWindow(EventBus& eventBus)
		{
		}

		virtual ~IWindow() = default;

		virtual bool	Create(const char* title, uint32 width, uint32 height) = 0;
		virtual bool	Destroy() = 0;
		virtual void	PollEvents() = 0;

		virtual bool	Resize(uint32 width, uint32 height) = 0;
		virtual bool	SetTitle(const char* title) = 0;
		virtual bool	SetVSync(bool enabled) = 0;
		virtual bool	SetVideoMode(WindowMode mode) = 0; 
		virtual bool	Maximize() = 0;
		virtual bool	Minimize() = 0;
		virtual int32	ShouldClose() = 0;

		virtual void*	GetNativeWindow() const = 0;
	};
}


#endif // !WINDOW_INTERFACE_H__INCLUDED
