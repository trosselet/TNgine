#ifndef APPLICATION_H__INCLUDED
#define APPLICATION_H__INCLUDED

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
	};
}



#endif // APPLICATION_H__INCLUDED