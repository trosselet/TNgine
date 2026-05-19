#pragma once

#define TNGINE_API_VULKAN
//#define TNGINE_API_DIRECTX12
//#define TNGINE_API_OPENGL


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