#include "File.h"

bool TNgine::FileSystem::File::Exists(const Path& path)
{
	return path.Exists();
}

std::unique_ptr<TNgine::FileSystem::FileHandle> TNgine::FileSystem::File::Open(const Path& path, FileMode mode)
{
	return std::make_unique<DiskHandle>(path, mode);
}
