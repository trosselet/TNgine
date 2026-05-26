#ifndef FILE_WATCHER_H__INCLUDED
#define FILE_WATCHER_H__INCLUDED

#include <Platform/FileSystem/IFileWatcher.h>
#include "WinFileWatcher.h"
#include "LinFileWatcher.h"
#include "MacFileWatcher.h"

#include <Core/Threads/Atomic.h>
#include <Core/Threads/Thread.h>

namespace TNgine
{
	namespace FileSystem
	{
		class FileWatcher
		{
		public:
#ifdef TNGINE_OS_WINDOWS
			using Watcher = WinFileWatcher;
#elif TNGINE_OS_LINUX
			using Watcher = LinFileWatcher;
#elif TNGINE_OS_MAC
			using Watcher = MacFileWatcher;
#endif

		public:
			static FileWatcher& Instance();
			~FileWatcher() = default;
			void Watch(const Path& path);
			void Unwatch(const Path& path);
			bool PopEvent(FileChangeEvent& event);

			void Start();
			void Stop();

		private:
			void Poll();
			void WatchLoop();

		private:
			Watcher m_Watcher;

			TNgine::Thread m_Thread;
			TNgine::Atomic<bool> m_Running = false;
		};
	}
}


#endif // !FILE_WATCHER_H__INCLUDED