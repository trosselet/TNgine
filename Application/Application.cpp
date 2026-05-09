#include "Application.h"

#include <Core/Math/Transform.hpp>
#include <Core/Logging/Logging.h>
#include <Core/Utils/Utils.hpp>

namespace TNgine
{
	void Application::Init()
	{
		Core::Log::Instance().Create();
	}
	void Application::Run()
	{
		// Main application loop
	}
	void Application::ShutDown()
	{
		// Clean up resources and shut down the application
	}
}