#ifndef FILE_H__INCLUDED
#define FILE_H__INCLUDED

#include <Core/include.h>
#include "FileHandle.h"
#include "FileHandle/DiskHandle.h"
#include "FileHandle/MemoryHandle.h"
#include "Path.h"

namespace TNgine
{
	namespace FileSystem
	{
		class File
		{
		public:
			static bool Exists(const Path& path);

			static std::unique_ptr<FileHandle> Open(const Path& path, FileMode mode);


		};
	}
}


#endif // !FILE_H__INCLUDED
