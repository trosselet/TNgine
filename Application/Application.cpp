#include "Application.h"

#include <Core/Logging/Logging.h>
#include <Core/Utils/Utils.hpp>
#include <Core/TMath.h>
#include <Core/Containers/DynArray.hpp>
#include <Core/Containers/HashMap.hpp> 
#include <Core/Utils/ProfileScope.hpp>


namespace TNgine
{
	void Application::Init()
	{
		Core::Log::Instance().Create();

		
	}

	void Application::Run()
	{
		while(true)
		{
			{
				PROFILE_SCOPE("Renderer::Init");

				PROFILE_TIMEPOINT("Buffers");

				PROFILE_TIMEPOINT("Meshes");

				PROFILE_TIMEPOINT("Shaders");
			}

			{
				PROFILE_SCOPE("Gameplay::Init");

				PROFILE_TIMEPOINT("Scripts");

				PROFILE_TIMEPOINT("Movements");

				PROFILE_TIMEPOINT("Tests");
			}
		}
	}

	void Application::ShutDown()
	{
		// Clean up resources and shut down the application
	}
}