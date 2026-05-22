#ifndef FILE_WATCHER_H__INCLUDED
#define FILE_WATCHER_H__INCLUDED

#include <Platform/FileSystem/IFileWatcher.h>
#include "WinFileWatcher.h"
#include "LinFileWatcher.h"
#include "MacFileWatcher.h"

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
			void Poll();
			bool PopEvent(FileChangeEvent& event);
		private:
			Watcher m_Watcher;
		};
	}
}


#endif // !FILE_WATCHER_H__INCLUDED