#ifndef APPLICATION_H__INCLUDED
#define APPLICATION_H__INCLUDED

#include <Core/include.h> 
#include <Platform/Window/WindowFactory.hpp>



namespace TNgine
{

	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;
		void Init();
		void Run();
		void ShutDown();

	private:
		void WatcherUpdate();

	private:
		LinearAllocator m_WindowAllocator{ sizeof(Window), "Window Allocator" };
		Window* mp_Window = nullptr;
		EventBus m_EventBus;
	};
}



#endif // APPLICATION_H__INCLUDED