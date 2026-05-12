#include "Application.h"

#include <Core/Logging/Logging.h>
#include <Core/Utils/Utils.hpp>
#include <Core/TMath.h>
#include <Core/Containers/DynArray.hpp>


#include <vector>
#include <array>

namespace TNgine
{
	void Application::Init()
	{
		Core::Log::Instance().Create();

		DynArray<int32> arr(4, 42);
		arr.Resize(8);
		arr.Assign(2, 3, 40);
		arr.Assign(2, {50, 25, 60});
		

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