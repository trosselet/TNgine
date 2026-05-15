#include "Application.h"

#include <Core/Logging/Logging.h>
#include <Core/Utils/Utils.hpp>
#include <Core/TMath.h>
#include <Core/Containers/DynArray.hpp>
#include <Core/Containers/HashMap.hpp>


#include <chrono>

class Timer
{
public:
	Timer(const std::string& name)
		: m_name(name)
	{
		m_start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		auto end = std::chrono::high_resolution_clock::now();

		auto duration =
			std::chrono::duration_cast<std::chrono::nanoseconds>(
				end - m_start);

		std::cout
			<< m_name
			<< " : "
			<< duration.count()
			<< " ms"
			<< std::endl;
	}

private:
	std::string m_name;

	std::chrono::high_resolution_clock::time_point m_start;
};
 

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