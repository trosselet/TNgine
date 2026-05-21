#ifndef DISK_FILE_PROVIDER_H__INCLUDED
#define DISK_FILE_PROVIDER_H__INCLUDED

#include "IVirtualFileProvider.h"

namespace TNgine
{
	namespace FileSystem
	{
		class DiskFileProvider : public IVirtualProvider
		{
		public:

			DiskFileProvider(const Path& path);
			~DiskFileProvider() = default;
			bool Exists(const Path& path) const override;
			std::unique_ptr<FileHandle> Open(const Path& path, FileMode mode) override;

		private:
			Path m_RootPath;
		};
	}
}

#endif // !DISK_FILE_PROVIDER_H__INCLUDED