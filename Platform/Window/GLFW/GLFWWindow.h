#ifndef GLFW_WINDOW_H__INCLUDED
#define GLFW_WINDOW_H__INCLUDED

#include "../IWindow.h"
#include "../WindowCreateInfo.h"

#include <GLFW/glfw3.h>

namespace TNgine
{
	class GLFWWindow : public IWindow
	{
	public:
		GLFWWindow(EventBus& eventBus);
		~GLFWWindow();

		bool	Create(const char* title, uint32 width, uint32 height) override;
		bool	Destroy() override;
		void	PollEvents() override;

		bool	Resize(uint32 width, uint32 height) override;
		bool	SetTitle(const char* title) override;
		bool	SetVSync(bool enabled) override;
		bool	SetVideoMode(WindowMode mode) override;
		bool	Maximize() override;
		bool	Minimize() override;
		int32	ShouldClose() override;

		void* GetNativeWindow() const override;

	private:
		void _InitializeGLFW();
		static void _ErrorCallback(int error, const char* description);

		static void _KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void _WindowCloseCallback(GLFWwindow* window);

	private:
		GLFWwindow* mp_Window;

		bool m_VSyncEnabled;
		WindowMode m_WindowMode;

		uint32 m_Width;
		uint32 m_Height;

		int m_WindowPosX;
		int m_WindowPosY;

		int m_WindowedWidth;
		int m_WindowedHeight;


		EventBus& m_EventBus;
	};
}


#endif // !GLFW_WINDOW_H__INCLUDED