#ifndef WIN_FILE_WATCHER_H__INCLUDED
#define WIN_FILE_WATCHER_H__INCLUDED


#include <queue>
#include <filesystem>
#include <Core/include.h>
#include "../FileSystem/Path.h"
#include "../FileSystem/IFileWatcher.h"

#ifdef TNGINE_OS_WINDOWS
#include <Windows.h>

namespace TNgine
{
	namespace FileSystem
	{
		class WinFileWatcher : public IFileWatcher
		{
		public:
			WinFileWatcher();
			virtual ~WinFileWatcher();
			virtual void Watch(const Path& path) override;
			virtual void Unwatch(const Path& path) override;
			virtual void Poll() override;
			virtual bool PopEvent(FileChangeEvent& event) override;
		private:

			struct WatchedEntry
			{
				HANDLE DirectoryHandle;
				Path Directory; 
				byte Buffer[4096];
			};

		private:

			DynArray<WatchedEntry> m_Watches;

			std::queue<FileChangeEvent> m_Events;
		};
	}
}
#endif // TNGINE_OS_WINDOWS


#endif // !WIN_FILE_WATCHER_H__INCLUDED
