#include "Application.h"

#include <Platform/Input/Input.h>

namespace TNgine
{
	static void OnKeyPressed(const KeyPressedEvent& e)
	{
		CLOG_INFO("Key Pressed: {} Repeat: {}", e.Key, e.Repeat);
	}

	static void OnWindowClose(const WindowCloseEvent&)
	{
		CLOG_WARN("Window Close Requested");
	}

	void Application::Init()
	{
		Core::Log::Instance().Create();

		mp_Window = AllocateObject<Window>(m_WindowAllocator, m_EventBus);
		mp_Window->Create("TNgine", 1280, 720);

		m_EventBus.KeyPressed.Subscribe(OnKeyPressed);
		m_EventBus.WindowClose.Subscribe(OnWindowClose);
	} 

	void Application::Run()
	{
		while (mp_Window->ShouldClose() < 1)
		{
			{			
				mp_Window->PollEvents(); 

				m_EventBus.Dispatch(); 

				if (Input::IsKeyDown(Key::F10))
				{
					mp_Window->SetVideoMode(WindowMode::Borderless);
				}
				if (Input::IsKeyDown(Key::F11))
				{
					mp_Window->SetVideoMode(WindowMode::Fullscreen);
				}


			} 



			Input::Update();

		}

	}

	void Application::ShutDown()
	{
		// Clean up resources and shut down the application
	}
}