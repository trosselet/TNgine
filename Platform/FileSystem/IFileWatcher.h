#ifndef I_FILE_WATCHER_H__INCLUDED
#define I_FILE_WATCHER_H__INCLUDED

#include "Path.h"

namespace TNgine
{
	namespace FileSystem
	{
		enum class FileAction
		{
			Added,
			Removed,
			Modified,
			Renamed
		};

		struct FileChangeEvent
		{
			FileAction Action;
			Path FilePath;
		};


		class IFileWatcher
		{
		public:
			virtual ~IFileWatcher() = default;

			virtual void Watch(const Path& path) = 0;

			virtual void Unwatch(const Path& path) = 0;

			virtual void Poll() = 0;

			virtual bool PopEvent(FileChangeEvent& event) = 0;
		};
	}
}



#endif // !I_FILE_WATCHER_H__INCLUDED
