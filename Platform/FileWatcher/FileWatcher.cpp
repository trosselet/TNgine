#include "FileWatcher.h"

TNgine::FileSystem::FileWatcher& TNgine::FileSystem::FileWatcher::Instance()
{
	static FileWatcher instance;
	return instance;
}

void TNgine::FileSystem::FileWatcher::Watch(const Path& path)
{
	m_Watcher.Watch(path);
}

void TNgine::FileSystem::FileWatcher::Unwatch(const Path& path)
{
	m_Watcher.Unwatch(path);
}

void TNgine::FileSystem::FileWatcher::Poll()
{
	m_Watcher.Poll();
}

bool TNgine::FileSystem::FileWatcher::PopEvent(FileChangeEvent& event)
{
	return m_Watcher.PopEvent(event);
}
