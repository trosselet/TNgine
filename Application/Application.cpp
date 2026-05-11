#include "Application.h"

#include <Core/Logging/Logging.h>
#include <Core/Utils/Utils.hpp>
#include <Core/TMath.h>


namespace TNgine
{
	void Application::Init()
	{
		Core::Log::Instance().Create();

		Matrix2x2 matA;
		Matrix2x2 matB(2.0f);

		matA *= matB;
		matA.Print();


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