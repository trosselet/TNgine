#include "GLFWWindow.h"

#include "../../Input/Input.h"

namespace TNgine
{
	static bool s_GLFWInitialized = false;
}

void TNgine::GLFWWindow::_ErrorCallback(int error, const char* description)
{
	CLOG_ERROR("GLFW Error ({0}): {1}", error, description);
}

void TNgine::GLFWWindow::_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GLFWWindow* pThis = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS)
	{
		Input::SetKey((Key)key, true);
		pThis->m_EventBus.KeyPressed.Push(KeyPressedEvent(key, false));
	}

	if (action == GLFW_REPEAT)
	{
		Input::SetKey((Key)key, true);
		pThis->m_EventBus.KeyPressed.Push(KeyPressedEvent(key, true));
	}

	if (action == GLFW_RELEASE)
	{
		Input::SetKey((Key)key, false);
		pThis->m_EventBus.KeyReleased.Push(KeyReleasedEvent(key));
	}

}

void TNgine::GLFWWindow::_WindowCloseCallback(GLFWwindow* window)
{
	GLFWWindow* pThis = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

	pThis->m_EventBus.WindowClose.Push(WindowCloseEvent());
}

void TNgine::GLFWWindow::_InitializeGLFW()
{
	if (s_GLFWInitialized)
		return;

#define GLFW_INCLUDE_NONE

	glfwSetErrorCallback(_ErrorCallback);

	if (!glfwInit())
	{
		CLOG_ERROR("Failed to initialize GLFW");
		return;
	}

	s_GLFWInitialized = true; 
}

TNgine::GLFWWindow::GLFWWindow(EventBus& eventBus) : IWindow(eventBus), m_EventBus(eventBus), mp_Window(nullptr), m_VSyncEnabled(false), m_WindowMode(WindowMode::Windowed)
{
	_InitializeGLFW();
}

TNgine::GLFWWindow::~GLFWWindow()
{
	Destroy();

	if (s_GLFWInitialized)
	{
		glfwTerminate();
		s_GLFWInitialized = false;
	}
}


bool TNgine::GLFWWindow::Create(const char* title, uint32 width, uint32 height)
{
	WindowCreateInfo info
	{
		title,
		width,
		height
	};

	mp_Window = glfwCreateWindow(
		info.Width,
		info.Height,
		info.Title,
		nullptr,
		nullptr
	);

	if (!mp_Window)
	{
		CLOG_ERROR("Failed to create GLFW window");
		return false;
	}

	glfwMakeContextCurrent(mp_Window);

	glfwSetWindowUserPointer(mp_Window, this);

	glfwSetKeyCallback(mp_Window, _KeyCallback);
	glfwSetWindowCloseCallback(mp_Window, _WindowCloseCallback);

	m_Width = width;
	m_Height = height;

	return true;
}

bool TNgine::GLFWWindow::Destroy()
{
	if (!mp_Window)
		return false;

	glfwDestroyWindow(mp_Window);
	mp_Window = nullptr;

	return true;
}

void TNgine::GLFWWindow::PollEvents()
{
	glfwPollEvents();
}

bool TNgine::GLFWWindow::Resize(uint32 width, uint32 height)
{
	if (!mp_Window)
		return false;

	glfwSetWindowSize(mp_Window, width, height);

	m_Width = width;
	m_Height = height;

	return true;
}

bool TNgine::GLFWWindow::SetTitle(const char* title)
{
	if (!mp_Window)
		return false;

	glfwSetWindowTitle(mp_Window, title);

	return true;
}

bool TNgine::GLFWWindow::SetVSync(bool enabled)
{
	if (!mp_Window)
		return false;

	glfwMakeContextCurrent(mp_Window);

	glfwSwapInterval(enabled ? 1 : 0);

	m_VSyncEnabled = enabled;

	return true;
}

bool TNgine::GLFWWindow::SetVideoMode(WindowMode mode)
{
	if (!mp_Window)
		return false;

	if (mode == m_WindowMode)
		mode = WindowMode::Windowed;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	if (!monitor)
		return false;

	const GLFWvidmode* videoMode =
		glfwGetVideoMode(monitor);

	if (!videoMode)
		return false;
	 
	if (m_WindowMode == WindowMode::Windowed)
	{
		glfwGetWindowPos(mp_Window, &m_WindowPosX, &m_WindowPosY);

		glfwGetWindowSize( mp_Window, &m_WindowedWidth, &m_WindowedHeight );
	}

	switch (mode)
	{
		case WindowMode::Windowed:
		{
			glfwSetWindowAttrib( mp_Window, GLFW_DECORATED, GLFW_TRUE );

			glfwSetWindowMonitor( mp_Window, nullptr, m_WindowPosX, m_WindowPosY, m_WindowedWidth, m_WindowedHeight, 0 );

			break;
		}

		case WindowMode::Borderless:
		{
			int monitorX, monitorY;

			glfwGetMonitorPos( monitor, &monitorX, &monitorY );

			glfwSetWindowMonitor( mp_Window, nullptr, monitorX, monitorY, videoMode->width, videoMode->height, 0 );

			glfwSetWindowAttrib( mp_Window, GLFW_DECORATED, GLFW_FALSE );

			break;
		}

		case WindowMode::Fullscreen:
		{
			glfwSetWindowAttrib( mp_Window, GLFW_DECORATED, GLFW_TRUE );

			glfwSetWindowMonitor( mp_Window, monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate );

			break;
		}
	}

	m_WindowMode = mode;

	return true;
}

bool TNgine::GLFWWindow::Maximize()
{
	if (!mp_Window)
		return false;

	glfwMaximizeWindow(mp_Window);

	return true;
}

bool TNgine::GLFWWindow::Minimize()
{
	if (!mp_Window)
		return false;

	glfwIconifyWindow(mp_Window);

	return true;
}

int32 TNgine::GLFWWindow::ShouldClose()
{
	if (!mp_Window)
		return true;

	return glfwWindowShouldClose(mp_Window);
}

void* TNgine::GLFWWindow::GetNativeWindow() const
{
	return mp_Window;
}




