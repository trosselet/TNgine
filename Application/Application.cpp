#include "Application.h"

#include <Core/include.h>

namespace TNgine
{
	void Application::Init()
	{
		Core::Log::Instance().Create();

		
	}

	void OnKeyPressed(const KeyPressEvent& e)
	{
		Core::Log::Instance().Info(LogTarget::CONSOLE_LOG, "Key Pressed: {0}, Repeat: {1}", e.keyCode, e.isRepeat);
	}

	void Application::Run()
	{
		KeyPressEvent keyEvent{ 0, false };
		EventQueue<KeyPressEvent> keyPressQueue;
		keyPressQueue.PushEvent(keyEvent);
		keyPressQueue.Subscribe(OnKeyPressed);
		keyPressQueue.Dispatch();
		
		PoolAllocator poolAllocator(sizeof(LinearAllocator), 8);

		LinearAllocator* pAllocator = AllocateObject<LinearAllocator>(poolAllocator, 1024 * 1024, "Main Linear Allocator");

		int32* x = static_cast<int32*>(TALLOC((*pAllocator), sizeof(int32)));

		//while(true)
		{
			//{
			//	PROFILE_SCOPE("Renderer::Init");
			//
			//	PROFILE_TIMEPOINT("Buffers");
			//
			//	PROFILE_TIMEPOINT("Meshes");
			//
			//	PROFILE_TIMEPOINT("Shaders");
			//}
			//
			//{
			//	PROFILE_SCOPE("Gameplay::Init");
			//
			//	PROFILE_TIMEPOINT("Scripts");
			//
			//	PROFILE_TIMEPOINT("Movements");
			//
			//	PROFILE_TIMEPOINT("Tests");
			//}

			//CONSOLECLR;
		}

		FreeObject(poolAllocator, pAllocator);
	}

	void Application::ShutDown()
	{
		// Clean up resources and shut down the application
	}
}