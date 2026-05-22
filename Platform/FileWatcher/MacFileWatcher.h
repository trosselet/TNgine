#ifndef MAC_FILE_WATCHER_H__INCLUDED
#define MAC_FILE_WATCHER_H__INCLUDED

#include <queue>
#include <filesystem>
#include <Core/include.h>
#include "../FileSystem/Path.h"
#include "../FileSystem/IFileWatcher.h"

#ifdef TNGINE_OS_MAC
#include <CoreServices/CoreServices.h>


namespace TNgine
{
	namespace FileSystem
	{
		class MacFileWatcher : public IFileWatcher
		{
		public:
			MacFileWatcher();
			~MacFileWatcher();
			virtual void Watch(const Path& path) override;
			virtual void Unwatch(const Path& path) override;
			virtual void Poll() override;
			virtual bool PopEvent(FileChangeEvent& event) override;
		private:

			static void Callback(ConstFSEventStreamRef streamRef, void* clientCallBackInfo, size_t numEvents, void* eventPaths, const FSEventStreamEventFlags eventFlags[], const FSEventStreamEventId eventIds[]);

		private:

			FSEventStreamRef m_Stream;

			std::queue<FileChangeEvent> m_Events;
		};
	}
}

#endif // TNGINE_OS_MAC

#endif // !MAC_FILE_WATCHER_H__INCLUDED