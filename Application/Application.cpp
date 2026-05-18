#include "Application.h"

#include <Core/Logging/Logging.h>
#include <Core/Utils/Utils.hpp>
#include <Core/TMath.h>
#include <Core/Containers/DynArray.hpp>
#include <Core/Containers/HashMap.hpp> 
#include <Core/Utils/ProfileScope.hpp>

#include <Core/Events/Events.h>
#include <Core/Events/EventQueue.hpp>

#include <Core/Memory/PoolAllocator.hpp>
#include <Core/Memory/StackAllocator.hpp>
#include <Core/Memory/LinearAllocator.hpp>

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
		//KeyPressEvent keyEvent{ 0, false };
		//EventQueue<KeyPressEvent> keyPressQueue;
		//keyPressQueue.PushEvent(keyEvent);
		//keyPressQueue.Subscribe(OnKeyPressed);
		//keyPressQueue.Dispatch();
		
		LinearAllocator allocator(4096 * 4096);
		int* x = static_cast<int*>(TALLOC(allocator, sizeof(int)));

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
	}

	void Application::ShutDown()
	{
		// Clean up resources and shut down the application
		int test = 0;

		//while (true)
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
	}
}