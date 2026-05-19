#ifndef WINDOW_FACTORY_H__INCLUDED
#define WINDOW_FACTORY_H__INCLUDED

#define TNGINE_WINDOW_GLFW

#include "IWindow.h"
#include "GLFW/GLFWWindow.h"

namespace TNgine
{
	class Window : public IWindow
	{
	public:
#ifdef TNGINE_WINDOW_GLFW
		using WindowType = GLFWWindow;
#endif // TNGINE_WINDOW_GLFW
#ifdef TNGINE_WINDOW_SDL2
		using WindowType = SDL2Window;
#endif // TNGINE_WINDOW_SDL2

	public:
		Window(EventBus& eventBus) : IWindow(eventBus), m_Window(eventBus)
		{
		}
		
		virtual ~Window()
		{
			Destroy();
		}

		bool Create(const char* title, uint32 width, uint32 height) override
		{
			return m_Window.Create(title, width, height);
		}

		bool Destroy() override
		{
			return m_Window.Destroy();
		}

		void PollEvents() override
		{
			m_Window.PollEvents();
		}

		bool Resize(uint32 width, uint32 height) override
		{
			return m_Window.Resize(width, height);
		}

		bool SetTitle(const char* title) override
		{
			return m_Window.SetTitle(title);
		}

		bool SetVSync(bool enabled) override
		{
			return m_Window.SetVSync(enabled);
		}

		bool SetVideoMode(WindowMode mode) override
		{
			return m_Window.SetVideoMode(mode);
		}

		bool Maximize() override
		{
			return m_Window.Maximize();
		}

		bool Minimize() override
		{
			return m_Window.Minimize();
		}

		int32 ShouldClose() override
		{
			return m_Window.ShouldClose();
		}

		void* GetNativeWindow() const override
		{
			return m_Window.GetNativeWindow();
		}

	private:
		WindowType m_Window;
	};
}

#endif // !WINDOW_FACTORY_H__INCLUDED