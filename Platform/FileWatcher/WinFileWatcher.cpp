#include "WinFileWatcher.h"

#ifdef TNGINE_OS_WINDOWS



TNgine::FileSystem::WinFileWatcher::WinFileWatcher()
{
}

TNgine::FileSystem::WinFileWatcher::~WinFileWatcher()
{
	for (auto& watch : m_Watches)
	{
		CloseHandle(watch.DirectoryHandle);
	}
}

void TNgine::FileSystem::WinFileWatcher::Watch(const Path& path)
{
	HANDLE handle = CreateFileA(path.String().c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);

	if (handle == INVALID_HANDLE_VALUE)
	{
		CLOG_ERROR("Failed to watch directory: {}", path.String());
		return;
	}

	WatchedEntry entry;

	entry.DirectoryHandle = handle;
	entry.Directory = path;

	m_Watches.PushBack(entry);
}

void TNgine::FileSystem::WinFileWatcher::Unwatch(const Path& path)
{
}

void TNgine::FileSystem::WinFileWatcher::Poll()
{
	for (auto& watch : m_Watches)
	{
		DWORD bytesReturned = 0;

		BOOL success = ReadDirectoryChangesW(watch.DirectoryHandle, watch.Buffer, sizeof(watch.Buffer), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE, &bytesReturned, nullptr, nullptr);

		if (!success)
		{
			continue;
		}

		FILE_NOTIFY_INFORMATION* info = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(watch.Buffer);

		do
		{
			std::wstring filename(info->FileName, info->FileNameLength / sizeof(WCHAR));

			FileChangeEvent event;

			event.FilePath = watch.Directory / Path(std::string(filename.begin(), filename.end()));

			switch (info->Action)
			{
				case FILE_ACTION_ADDED :
				{
					event.Action = FileAction::Added;
					break;
				}
				case FILE_ACTION_REMOVED :
				{
					event.Action = FileAction::Removed;
					break;
				}
				case FILE_ACTION_MODIFIED :
				{
					event.Action = FileAction::Modified;
					break;
				}
				case FILE_ACTION_RENAMED_NEW_NAME :
				{
					event.Action = FileAction::Renamed;
					break;
				}
				default:
					break;
			}

			m_Events.push(event);

			if (info->NextEntryOffset == 0)
			{
				break;
			}

			info = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<byte*>(info) + info->NextEntryOffset);


		} while (true);
	}
}

bool TNgine::FileSystem::WinFileWatcher::PopEvent(FileChangeEvent& event)
{
	if (m_Events.empty())
	{
		return false;
	}

	event = m_Events.front();
	m_Events.pop();

	return true;
}

#endif // TNGINE_OS_WINDOWS