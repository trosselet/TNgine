#include "MacFileWatcher.h"

#ifdef TNGINE_OS_MAC



TNgine::FileSystem::MacFileWatcher::MacFileWatcher() : m_Stream(nullptr)
{
}

TNgine::FileSystem::MacFileWatcher::~MacFileWatcher()
{
    if (m_Stream)
    {
        FSEventStreamStop(m_Stream);

        FSEventStreamInvalidate(m_Stream);

        FSEventStreamRelease(m_Stream);
    }
}

void TNgine::FileSystem::MacFileWatcher::Watch(const Path& path)
{
    CFStringRef pathRef = CFStringCreateWithCString( nullptr, path.String().c_str(), kCFStringEncodingUTF8);

    CFArrayRef paths = CFArrayCreate(nullptr, static_cast<const void**>(&pathRef), 1, nullptr);

    FSEventStreamContext context
    {
        0,
        this,
        nullptr,
        nullptr,
        nullptr
    };

    m_Stream = FSEventStreamCreate(nullptr, &MacFileWatcher::Callback, &context, paths, kFSEventStreamEventIdSinceNow, 0.1, kFSEventStreamCreateFlagFileEvents);

    if (!m_Stream)
    {
        return;
    }

    FSEventStreamScheduleWithRunLoop(m_Stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);

    FSEventStreamStart(m_Stream);

    CFRelease(paths);
    CFRelease(pathRef); 
}

void TNgine::FileSystem::MacFileWatcher::Unwatch(const Path& path)
{
}

void TNgine::FileSystem::MacFileWatcher::Poll()
{
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, true);
}

bool TNgine::FileSystem::MacFileWatcher::PopEvent(FileChangeEvent& event)
{
    if (m_Events.empty())
    {
        return false;
    }

    event = m_Events.front();
    m_Events.pop();

    return true;
}

void TNgine::FileSystem::MacFileWatcher::Callback(ConstFSEventStreamRef streamRef, void* clientCallBackInfo, size_t numEvents, void* eventPaths, const FSEventStreamEventFlags eventFlags[], const FSEventStreamEventId eventIds[])
{
    auto* watcher = static_cast<MacFileWatcher*>(clientCallBackInfo);

    char** paths = static_cast<char**>(eventPaths);

    for (size_t i = 0; i < numEvents; ++i)
    {
        FileChangeEvent e;

        e.FilePath = Path(paths[i]);

        auto flags = eventFlags[i];

        if (flags & kFSEventStreamEventFlagItemCreated)
        {
            e.Action = FileAction::Added;
        }
        else if (flags & kFSEventStreamEventFlagItemRemoved)
        {
            e.Action = FileAction::Removed;
        }
        else if (flags & kFSEventStreamEventFlagItemRenamed)
        {
            e.Action = FileAction::Renamed;
        }
        else
        {
            e.Action = FileAction::Modified;
        }

        watcher->m_Events.push(e);
    }
}

#endif // TNGINE_OS_MAC