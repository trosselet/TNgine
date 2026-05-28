#include "Application.h"

#include <Platform/Input/Input.h>
#include <Platform/FileSystem/VirtualFileSystem.h>
#include <Platform/FileWatcher/FileWatcher.h>

#include <Backends/Vulkan/VulkanBaseCode.h>

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

		FileSystem::VirtualFileSystem::Instance().Mount("Textures://", std::make_shared<FileSystem::DiskFileProvider>("Assets/Textures/"));
		FileSystem::VirtualFileSystem::Instance().Mount("Models://", std::make_shared<FileSystem::DiskFileProvider>("Assets/Models/"));
		FileSystem::VirtualFileSystem::Instance().Mount("Audio://", std::make_shared<FileSystem::DiskFileProvider>("Assets/Audio/"));

		{
			auto handle = FileSystem::VirtualFileSystem::Instance().Open("Textures://dwall.jpg", FileSystem::FileMode::Read);
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

		FileSystem::FileWatcher::Instance().Watch("Assets/");
		FileSystem::FileWatcher::Instance().Start();

		JobSystem::Init(ThreadUtils::GetHardwareThreadCount());

		VulkanInit init;
		init.Init();

	} 

	void Application::Run()
	{
		while (mp_Window->ShouldClose() < 1)
		{
			{			
				mp_Window->PollEvents(); 

				m_EventBus.Dispatch(); 

				if (Input::IsKeyPressed(Key::F10))
				{
					mp_Window->SetVideoMode(WindowMode::Borderless);
				}
				if (Input::IsKeyPressed(Key::F11))
				{
					mp_Window->SetVideoMode(WindowMode::Fullscreen);
				}

				WatcherUpdate();
			} 



			Input::Update();

		}

	}

	void Application::ShutDown()
	{
		FileSystem::FileWatcher::Instance().Stop();
		JobSystem::Wait();
		JobSystem::Shutdown();
	}

	void Application::WatcherUpdate()
	{
		FileSystem::FileChangeEvent e;

		while (FileSystem::FileWatcher::Instance().PopEvent(e))
		{
			switch (e.Action)
			{
			case FileSystem::FileAction::Added:

				CLOG_INFO("Added: {}", e.FilePath.String());
				break;

			case FileSystem::FileAction::Removed:

				CLOG_INFO("Removed: {}", e.FilePath.String());
				break;

			case FileSystem::FileAction::Modified:

				CLOG_INFO("Modified: {}", e.FilePath.String());
				break;

			case FileSystem::FileAction::Renamed:

				CLOG_INFO("Renamed: {}", e.FilePath.String());
				break;
			}
		}
	}
}