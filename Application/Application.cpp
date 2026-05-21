#include "Application.h"

#include <Platform/Input/Input.h>
#include <Platform/FileSystem/VirtualFileSystem.h>

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

		FileSystem::VirtualFileSystem vfs;

		vfs.Mount("Textures://", std::make_shared<FileSystem::DiskFileProvider>("Assets/Textures/"));
		vfs.Mount("Models://", std::make_shared<FileSystem::DiskFileProvider>("Assets/Models/"));
		vfs.Mount("Audio://", std::make_shared<FileSystem::DiskFileProvider>("Assets/Audio/"));

		{
			auto handle = vfs.Open("Textures://dwall.jpg", FileSystem::FileMode::Read);
			if (handle != nullptr)
			{
				DynArray<byte> buffer(handle->Size());
				handle->Read(buffer.Data(), buffer.Size());
				CLOG_INFO("Read {} bytes from dwall.jpg", buffer.Size());
			}
			else
			{
				CLOG_ERROR("Failed to open dwall.jpg");
			}
		}

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