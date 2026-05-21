#include "MemoryFileProvider.h"

#include "../FileHandle/MemoryHandle.h"

void TNgine::FileSystem::MemoryFileProvider::RegisterFile(const TNgine::FileSystem::Path& path, const TNgine::DynArray<byte>& data)
{
}

bool TNgine::FileSystem::MemoryFileProvider::Exists(const TNgine::FileSystem::Path& path) const
{
	return false;
}

std::unique_ptr<TNgine::FileSystem::FileHandle> TNgine::FileSystem::MemoryFileProvider::Open(const TNgine::FileSystem::Path& path, FileMode mode)
{
	auto it = m_Files.Find(path);

	if (it == nullptr)
	{
		return nullptr;
	}

	return std::make_unique<MemoryHandle>(*it);
}
