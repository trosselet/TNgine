#ifndef I_VIRTUAL_FILE_PROVIDER_H__INCLUDED
#define I_VIRTUAL_FILE_PROVIDER_H__INCLUDED

#include "../Path.h"
#include "../FileHandle.h"



namespace TNgine
{
	namespace FileSystem
	{
		class IVirtualProvider
		{
		public:

			virtual ~IVirtualProvider() = default;
			virtual bool Exists(const Path& path) const = 0;
			virtual std::unique_ptr<FileHandle> Open(const Path& path, FileMode mode) = 0;
		};
	}
}

#endif // !I_VIRTUAL_FILE_PROVIDER_H__INCLUDED