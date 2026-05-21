#include "FileHandle.h"

TNgine::FileSystem::FileHandle::FileHandle(const Path& path) : m_Path(path)
{
}

const TNgine::FileSystem::Path& TNgine::FileSystem::FileHandle::GetPath() const
{
	return m_Path;
}