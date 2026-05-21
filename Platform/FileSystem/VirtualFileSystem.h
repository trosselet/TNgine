#ifndef VIRTUAL_FILE_SYSTEM_H__INCLUDED
#define VIRTUAL_FILE_SYSTEM_H__INCLUDED

#include "FileProvider/IVirtualFileProvider.h"
#include "FileProvider/DiskFileProvider.h"
#include "FileProvider/MemoryFileProvider.h"
#include "Path.h"

namespace TNgine
{
	namespace FileSystem
	{
		class VirtualFileSystem
		{
		public:

			void Mount(const Path& virtualPath, std::shared_ptr<IVirtualProvider> provider);

			bool Exists(const Path& path);

			std::unique_ptr<FileHandle> Open(const Path& path, FileMode mode);

		private:
			struct MountPoint
			{
				Path VirtualRoot;

				std::shared_ptr<IVirtualProvider> Provider;
			};


		private:
			DynArray<MountPoint> m_MountPoints;
		};
	}
}

#endif // !VIRTUAL_FILE_SYSTEM_H__INCLUDED