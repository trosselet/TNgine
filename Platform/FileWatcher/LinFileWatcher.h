#ifndef LIN_FILE_WATCHER_H__INCLUDED
#define LIN_FILE_WATCHER_H__INCLUDED

#include <queue> 
#include <Core/include.h>
#include "../FileSystem/Path.h"
#include "../FileSystem/IFileWatcher.h"

#ifdef TNGINE_OS_LINUX
#include <sys/inotify.h>
#include <unistd.h>


namespace TNgine
{
	namespace FileSystem
	{
		class LinFileWatcher : public IFileWatcher
		{
		public:
			LinFileWatcher();
			~LinFileWatcher();
			virtual void Watch(const Path& path) override;
			virtual void Unwatch(const Path& path) override;
			virtual void Poll() override;
			virtual bool PopEvent(FileChangeEvent& event) override;
		private:

			int m_InotifyFd;

			HashMap<int, Path> m_WatchDescriptors;

			std::queue<FileChangeEvent> m_Events;
		};
	}
}
#endif // TNGINE_OS_LINUX


#endif // !LIN_FILE_WATCHER_H__INCLUDED