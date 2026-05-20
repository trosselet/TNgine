#pragma once


#include "Application.h"
#include <Core/Memory/AllocatorTracker.hpp>

TNgine::Application* CreateApplication()
{
	return new TNgine::Application();
}

int main(int argc, char** argv)
{ 
	auto app = CreateApplication();

	app->Init();
	app->Run();
	app->ShutDown();

	delete app;

	return 0;
}