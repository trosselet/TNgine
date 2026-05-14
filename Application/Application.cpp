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
		//arr.Assign(2, 3, 40);
		//arr.Assign(2, {50, 25, 60});
		
		DynArray<int32> arr2;
		bool empty = arr2.Empty();
		arr2 = arr;
		arr2.Erase(0);
		arr2 = arr;
		arr2.Erase(0, 2);
		int32 r = arr2.PopBack();
		int32 t = arr2.PopFront();
		arr2.Swap(arr);
		arr2.PushFront(0);
		arr2.Insert(0, 5);
		arr2.Insert(0, {5, 4, 2, 3});

		for (auto number : arr2)
		{
			CLOG_INFO(std::to_string(number));
		}

		arr2.Clear();

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