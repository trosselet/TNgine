#include "DiskFileProvider.h"

#include "../FileHandle/DiskHandle.h"

TNgine::FileSystem::DiskFileProvider::DiskFileProvider(const Path& path) : m_RootPath(path)
{
}

bool TNgine::FileSystem::DiskFileProvider::Exists(const TNgine::FileSystem::Path& path) const
{
	return (m_RootPath / path).Exists();
}

std::unique_ptr <TNgine::FileSystem::FileHandle> TNgine::FileSystem::DiskFileProvider::Open(const TNgine::FileSystem::Path& path, TNgine::FileSystem::FileMode mode)
{
	return std::make_unique<DiskHandle>((m_RootPath / path), mode);
}
