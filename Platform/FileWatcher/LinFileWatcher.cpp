#include "LinFileWatcher.h"

#ifdef TNGINE_OS_LINUX



#include <errno.h>
#include <string.h>

TNgine::FileSystem::LinFileWatcher::LinFileWatcher()
{
    m_InotifyFd = inotify_init1(IN_NONBLOCK);

    if (m_InotifyFd < 0)
    {
        CLOG_ERROR("Failed to initialize inotify");
    }
}

TNgine::FileSystem::LinFileWatcher::~LinFileWatcher()
{
    if (m_InotifyFd >= 0)
    {
        close(m_InotifyFd);
    }
}

void TNgine::FileSystem::LinFileWatcher::Watch(const Path& path)
{
    int wd = inotify_add_watch(m_InotifyFd, path.String().c_str(), IN_CREATE | IN_DELETE | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO);

    if (wd < 0)
    {
        CLOG_ERROR("Failed to watch {}", path.String());
        return;
    }

    m_WatchDescriptors[wd] = path;
}

void TNgine::FileSystem::LinFileWatcher::Unwatch(const Path& path)
{
    for (auto& [wd, watchPath] : m_WatchDescriptors)
    {
        if (watchPath == path)
        {
            inotify_rm_watch(m_InotifyFd, wd);

            m_WatchDescriptors.Remove(wd);

            return;
        }
    }
}

void TNgine::FileSystem::LinFileWatcher::Poll()
{
    constexpr size_t BufferSize = 4096;

    char buffer[BufferSize];

    ssize_t length = read(m_InotifyFd, buffer, BufferSize);

    if (length <= 0)
    {
        return;
    }

    size_t i = 0;

    while (i < length)
    {
        auto* event = reinterpret_cast<inotify_event*>(&buffer[i]);

        auto it = m_WatchDescriptors.Find(event->wd);

        if (it != nullptr)
        {
            Path fullPath = (*it) / Path(event->name);

            FileChangeEvent e;

            e.FilePath = fullPath;

            if (event->mask & IN_CREATE)
            {
                e.Action = FileAction::Added;
            }
            else if (event->mask & IN_DELETE)
            {
                e.Action = FileAction::Removed;
            }
            else if (event->mask & IN_MODIFY)
            {
                e.Action = FileAction::Modified;
            }
            else if (event->mask & IN_MOVED_FROM || event->mask & IN_MOVED_TO)
            {
                e.Action = FileAction::Renamed;
            }

            m_Events.push(e);
        }

        i += sizeof(inotify_event) + event->len;
    }
}

bool TNgine::FileSystem::LinFileWatcher::PopEvent(FileChangeEvent& event)
{
    if (m_Events.empty())
    {
        return false;
    }

    event = m_Events.front();
    m_Events.pop();

    return true;
}

#endif // TNGINE_OS_LINUX