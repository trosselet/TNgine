#include "VirtualFileSystem.h"

void TNgine::FileSystem::VirtualFileSystem::Mount(const TNgine::FileSystem::Path& virtualPath, std::shared_ptr<TNgine::FileSystem::IVirtualProvider> provider)
{
	MountPoint mountPoint;

	mountPoint.VirtualRoot = virtualPath;
	mountPoint.Provider = provider;

	m_MountPoints.PushBack(mountPoint);
}

bool TNgine::FileSystem::VirtualFileSystem::Exists(const TNgine::FileSystem::Path& path)
{
	for (const auto& mountPoint : m_MountPoints)
	{
		if (path.StartsWith(mountPoint.VirtualRoot))
		{
			Path localPath = path.LexicallyRelative(mountPoint.VirtualRoot);

			return mountPoint.Provider->Exists(localPath);
		}
	}

	return false;
}

std::unique_ptr<TNgine::FileSystem::FileHandle> TNgine::FileSystem::VirtualFileSystem::Open(const TNgine::FileSystem::Path& path, TNgine::FileSystem::FileMode mode)
{
	for (const auto& mountPoint : m_MountPoints)
	{
		if (path.StartsWith(mountPoint.VirtualRoot))
		{
			Path localPath = path.LexicallyRelative(mountPoint.VirtualRoot);

			return mountPoint.Provider->Open(localPath, mode);
		}
	}

	return nullptr;
}
