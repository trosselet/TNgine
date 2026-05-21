#ifndef MEMORY_FILE_PROVIDER_H__INCLUDED
#define MEMORY_FILE_PROVIDER_H__INCLUDED

#include "IVirtualFileProvider.h"

namespace TNgine
{
	namespace FileSystem
	{
		class MemoryFileProvider : public IVirtualProvider
		{
		public:

			~MemoryFileProvider() = default;
			void RegisterFile(const Path& path, const DynArray<byte>& data);
			bool Exists(const Path& path) const override;
			std::unique_ptr<FileHandle> Open(const Path& path, FileMode mode) override;

		private:
			HashMap<Path, DynArray<byte>> m_Files;
		};
	}
}

#endif // !MEMORY_FILE_PROVIDER_H__INCLUDED