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
		arr.Resize(6);
		arr.PushBack(6);
		arr.Reserve(12);
		arr.Resize(2);
		
		std::vector<int32> arr2(4, 42);
		arr2.resize(2);
		arr2.push_back(6);
		arr2.reserve(12);
		arr2.resize(2);

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